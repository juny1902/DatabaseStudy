
/***********************************************************

				어댑티드 자율주행및 자동주차 시스템

				A반 1조 박준영 21303014
						노남호 21103018

				[작품개요]

				라인을 따라 주행하며 장애물에 충돌하지 않고 안전하게
				목표 지점에 자동 주차하는 자동차 자율주행 시스템

				[제작일지]

				1. 작품의 일부기능 구현 (라인트레이서와 초음파센서 융합)
				2. 1에 기능 추가 (라인주행후 목표 색상 탐색)
				3. 2까지 구현된 기능 문제점 수정 (목표거리 보정, 인식색상 안정화)
				4. 3까지 구현된 기능에 추가기능 구현 (장애물 근접시 비상벨과 LED 점등)
				5. 최종적으로 목표지점에 도착시 안내음을 울리도록 구현 (초음파센서 근접 or 목표객체 크기 일정치 이상 감지)
				6. 그 외 안정화 작업
				7. 작동속도 향상을 위한 최적화

				[작동순서]

				1.	목표 추적 기능을 위한 목표 색상 설정.
				2.	라인트레이서로서의 기능 수행.
				3.	2의 기능을 수행중 장애물 검출시 비상정지.
				4.	2~3 의 기능 수행 후 목표 추적 시작.
				5.	추적을 완료(장애물 근접 or 객체 근접) 하면 안내음과 함께 프로그램 종료.

				[작동환경]

				1.	영상으로 부터 색상 검출시 휘도에 매우 민감하므로
				반사광이 잘 생기지 않는 물체를 이용하거나 조도가 약한 방에서 실험하도록 한다.
				2.	장애물 인식 거리는 12[cm] 미만으로 한다. (앞차와의 거리 유지)
				3.	라인 인식 폭은 일반적인 절연테이프의 2배인 약 2.5[cm]로 한다.
				4.	트랙의 반경은 약 45[cm]로 한다.
				5.	추적물체의 색상은 적,청,녹 의 3종으로 녹색은 인식률이 비교적 낮다.
				6.	라인 인식에 문제가 있을시 일단 직진하며 다시 라인을 찾는다.

				최종수정일 : 2016년 10월 7일

				************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <ctype.h>

#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include "camera.h"
#include "keyboard.h"
#include "display.h"
#include "api.h"
#include "PanTilt_protocol.h"
#include "uart_api.h"
#include "robot_protocol.h"

#define CAMERA_DEVICE        "/dev/camera"
enum { NONE, NO_FIND, MOVE_CENTER, MOVE_PAN_RBCAR, GO_MOVE };

// 전역변수 선언
int dev;
unsigned char red = 0, blue = 0, green = 0;
unsigned short rgb[240 * 320];
unsigned short left_us, right_us;
colmap col;
colmap Scan_pixel(unsigned char *r, unsigned char *g, unsigned char *b);

// 메소드 선언
void Emer_Stop(void);
void Job_Finished(void);
void Find_TargetPoint(IplImage *img, int *cx, int *cy, int *size);


int main()
{
	int state_flag = NO_FIND; // 상태 플래그
	int flag_finish = 0; // 프로그램 종료 여부 플래그

	int x, y, color, loop = 1; // 좌표와 색상
	int Y1, Cb, Cr; // YCbCr 색상계 색상 변수
	int cx = 160, cy = 120; // 바운더리

	int i; // 카운트 변수

	int bnd_box = 0; // 인식된 물체의 크기값 변수

	int pan_deg = 0, tilt_deg = 0, Motor_speed = 0x200;

	int search_flag = 0;
	unsigned char Line_Value, tmp_line = 0xff;
	dev = user_uart2_open();

	if (dev < 0)
	{
		printf("\n /dev/ttySAC3 Open error!");
		exit(0);
	}


	user_uart2_config();

	RoboCAR_PanTilt_Control(pan_deg, tilt_deg, Motor_speed);

	dev = user_uart1_open("SAC1");

	if (dev < 0)
	{
		printf("\n UART1 Open error!");
		exit(0);
	}

	user_uart1_config(115200, 8, UART_PARNONE, 1);
	RoboCAR_AllMotor_Control(STOP, 0);

	Init_FB();
	init_keyboard();

	dev = open(CAMERA_DEVICE, O_RDWR);

	if (dev < 0) {
		printf("Error: cannot open /dev/camera.\n");
		exit(1);
	}

	IplImage *img = NULL;

	img = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);



	Motor_speed = 0x200;

	printf("**************************\n");
	printf(" RoboCAR Auto Parking & Driving\n");
	printf("**************************\n");

	col = Scan_pixel(&red, &green, &blue); // 색 인식 함수.

	RoboCAR_AllMotor_Control(STOP, 0);
	while (1)
	{
		if (kbhit()) break;
		if (flag_finish == 1) break;

		Line_Value = RoboCAR_Get_InfraredRay_Data();

		left_us = RoboCAR_Get_Left_UltraSonic();
		right_us = RoboCAR_Get_Right_UltraSonic();


		printf("InfraredRay = 0x%x, left_us/right_us = %4d/%4d  [cm]\n", Line_Value, left_us, right_us);

		if ((left_us < 12 || right_us < 12) == 1) // 라인추적중 정지거리
		{
			Emer_Stop(); // 비상등 점멸및 경고음 출력
			RoboCAR_FrontLED_Control(0); // 비상정지중 조작한것들을 초기화
			RoboCAR_BackLED_Control(0);
			RoboCAR_Buzzer_Control(0);
		}
		else
		{


			switch (Line_Value) {

				//전진
			case 0xE7:  // 1110 0111
			case 0xEF:  // 1110 1111
			case 0xC3:  // 1100 0011
			case 0xF7:  // 1111 0111
				RoboCAR_AllMotor_Control(FORWARD, 50); // 뒤에 숫자 = 속도
				break;

				//좌회전
			case 0xF3: //1111 0011
			case 0xFB: //1111 1011 *
			case 0xF1: //1111 0001
			case 0xF9: //1111 1001
				RoboCAR_LeftMotor_Control(FORWARD, 20);
				RoboCAR_RightMotor_Control(FORWARD, 70);
				break;

				//좌급회
			case 0xF8: // 1111 1000
			case 0xFC: // 1111 1100
			case 0xFD: // 1111 1101
			case 0xFE: // 1111 1110
				RoboCAR_LeftMotor_Control(BACKWARD, 100);
				RoboCAR_RightMotor_Control(FORWARD, 100);
				break;

				//우회전
			case 0xCF: // 1100 1111
			case 0xDF: // 1101 1111
			case 0x9F: // 1001 1111
			case 0x8F: // 1000 1111 *
				RoboCAR_LeftMotor_Control(FORWARD, 70);
				RoboCAR_RightMotor_Control(FORWARD, 20);
				break;

				//우급회
			case 0x1F: //0001 1111
			case 0x3F: //0011 1111
			case 0xBF: //1011 1111
			case 0x7F: //0111 1111
				RoboCAR_LeftMotor_Control(FORWARD, 100);
				RoboCAR_RightMotor_Control(BACKWARD, 100);
				break;

				// 정지후 주차 루틴 수행
			case 0xFF:
				RoboCAR_AllMotor_Control(FORWARD, 80);
				sleep(0.7);
				RoboCAR_AllMotor_Control(STOP, 0);
				while (loop) // 앞서 인식한 색상 찾아 스캔
				{

					if (kbhit() != 0) break;
					if (flag_finish == 1) // 추적완료 플래그 성립시
					{
						Job_Finished();
						loop = 0; // while(loop) 탈출
					}
					/*
					  영상출력 및 화면에서 타겟의 x,y,크기를 리턴한다.
					  */
					write(dev, NULL, 1);
					read(dev, rgb, CIS_IMAGE_SIZE);
					RGB2cvIMG(img, rgb, 320, 240);

					Find_TargetPoint(img, &cx, &cy, &bnd_box);
					fb_display_IplImage(img, 240, 120);
					left_us = RoboCAR_Get_Left_UltraSonic();
					right_us = RoboCAR_Get_Right_UltraSonic();
					if ((left_us < 25) || (right_us < 25)) // 뒤에숫자 (25) 거리 cm 추적중 물체근접
					{ // 정지할때 거리
						RoboCAR_AllMotor_Control(STOP, 0);
						flag_finish = 1;
						// loop = 0; // 이 문장이 수행되면 가까이 도착후, 정지함
					}
					printf("cx,cy = (%d,%d),size = %d ----- left_us/right_us = %4d/%4d  [cm]\n", cx, cy, bnd_box, left_us, right_us);
					/*
					  좌표값에 따른 플래그 변화
					  */
					if (cx>90 && cx<170) // 물체가 중앙 정렬되었을때 직진할 중앙의 범위
					{
						if (state_flag == NO_FIND) state_flag = MOVE_CENTER;
						else if (state_flag == MOVE_CENTER) state_flag = MOVE_PAN_RBCAR;
					}
					else if (cx == 0) // 물체의 위치가 없음 = 못찾음
					{
						state_flag = NO_FIND;

					}
					else // 그 외 경우 (범위 밖에 있을 경우)
					{
						if (bnd_box > 1000) state_flag = MOVE_CENTER; // 일정 크기 이상의 물체만 찾는다.
						else state_flag = NO_FIND; // 크기 미만이면 NO_FIND (못찾은 것으로 간주)
					}
					/*
					  플래그값에 대한 스테이트 머신
					*/
					switch (state_flag)
					{
						case MOVE_CENTER://팬틸트모터 중앙 정렬
							printf("MOVE_CENTER\n");
							if (cx > 0 && cx <= 140)
							{
								if (pan_deg > 40)  pan_deg = 40;
								else      pan_deg += 5;
							}
							else if (cx >= 180)
							{
								if (pan_deg < -40) pan_deg = -40;
								else      pan_deg -= 5;
							}		
							if (cy > 0 && cy <= 100)
							{
								if (tilt_deg>20)	tilt_deg = 20;
								else			tilt_deg += 5;
							}
							else if (cy >= 140)
							{
								if (tilt_deg<-20)	tilt_deg = -20;
								else	tilt_deg -= 5;
							}
							RoboCAR_PanTilt_Control(pan_deg, tilt_deg, Motor_speed);
							break;

						case MOVE_PAN_RBCAR: // 로보카, 팬모터 정면바라보도록 정렬
							printf("MOVE_PAN_RBCAR %d\n", pan_deg);

							//바닥상태에 따라 바퀴가 헛도는 경우도 있으므로, 상황에 따라 pan_deg함수에 상수값을 추가할것
							if (abs(pan_deg) >= 10) {
								if (pan_deg > 0)
								{
									RoboCAR_Move_Angle(LEFT_ROTATION, 100, (pan_deg));
								}
								else
								{
									RoboCAR_Move_Angle(RIGHT_ROTATION, 100, abs(pan_deg));
								}

								pan_deg = 0;
								RoboCAR_PanTilt_Control(pan_deg, tilt_deg, Motor_speed);
							}
							state_flag = GO_MOVE;

							break;

						case GO_MOVE: // 타겟의 크기에 따른 로보카 이동
							printf("GO_MOVE\n");

							if (bnd_box > 0 && bnd_box < 45000) // 45000 물체크기에 따른 정지거리
							{// 추적 거리, 박스가 0보다 크고 a보다 작으면 앞으로 쭉
								RoboCAR_AllMotor_Control(FORWARD, 60);
							}
							// 8000 = f280, 9000 = f260, 10000 = , 11000 = OVER
							else if (bnd_box > 45000)
							{ // 정지할때 거리
								RoboCAR_AllMotor_Control(STOP, 0);
								flag_finish = 1;
								// loop = 0; // 이 문장이 수행되면 가까이 도착후, 정지함
							}
							break;

						case NO_FIND: // 중간에 인식하지 못한 경우
							printf("NO_FIND\n");
							if (search_flag == 0)
							{
								search_flag = 1;
								pan_deg = -70;
							}
							else
							{
								pan_deg += 10;
								if (pan_deg > 70)
								{
									search_flag = 0;
									pan_deg = -70;
								}
							}
							RoboCAR_PanTilt_Control(pan_deg, tilt_deg, Motor_speed);
							break;
					}//end switch
				}//end while
				break;

				// 불분명한 값이 검출되었을때
				/*
				RoboCAR_LeftMotor_Control(FORWARD, 50);
				RoboCAR_RightMotor_Control(FORWARD, 50);
				*/
			}// end switch
		}

	}//end while

	RoboCAR_AllMotor_Control(STOP, 0);

	user_uart1_close();
	close_keyboard();

	return 0;
}




/***************/
/* 함수 정의부 */
/***************/

void Emer_Stop(void)
{
	RoboCAR_AllMotor_Control(STOP, 0);
	RoboCAR_Buzzer_Control(100);
	RoboCAR_FrontLED_Control(100);
	RoboCAR_BackLED_Control(100);
	usleep(50 * 1000); // 50ms씩 대기
}

void Job_Finished(void) // 삐비비빅! 하며 정지.
{
	int cnt = 8;
	RoboCAR_AllMotor_Control(STOP, 0);
	while (cnt)
	{
		RoboCAR_Buzzer_Control(100);
		RoboCAR_FrontLED_Control(100);
		RoboCAR_BackLED_Control(100);
		usleep(50 * 1000); // 50ms씩 대기
		RoboCAR_Buzzer_Control(0);
		RoboCAR_FrontLED_Control(0);
		RoboCAR_BackLED_Control(0);
		usleep(50 * 1000);
		cnt--;
	}

}
void Find_TargetPoint(IplImage *img, int *cx, int *cy, int *size)
{
	int x, y, num;

	num = FindColor(col, red, green, blue, img);

	if (num > 0)
	{
		*cx = (int)reg[0].cen_x;
		*cy = (int)reg[0].cen_y;
		for (y = 0; y < img->height; y++)
			cvSet2D(img, y, *cx, CV_RGB(80, 255, 80));
		for (x = 0; x < img->width; x++)
			cvSet2D(img, *cy, x, CV_RGB(80, 255, 80));

		*size = (int)((reg[0].x2 - reg[0].x1) * (reg[0].y2 - reg[0].y1));
	}
	else
	{
		*cx = 0; *cy = 0; *size = 0;
	}

}

colmap Scan_pixel(unsigned char *r, unsigned char *g, unsigned char *b)
{
	int x, y, color;
	IplImage *img = NULL;
	int Y1, Cb, Cr;
	int i;

	int cx = 160, cy = 120;
	int tmp_r = 0, tmp_g = 0, tmp_b = 0;
	char ch;

	img = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);

	printf("\n Select parking lot color...");
	printf("\n w,s,a,d and space");
	printf("\n please Select color...push the spacebar\n");

	while (1) {
		ch = 0;
		if (kbhit() != 0) ch = readch();

		switch (ch) {
		case 'w':
		case 'W':
			cy -= 5;
			break;
		case 's':
		case 'S':
			cy += 5;
			break;

		case 'a':
		case 'A':
			cx -= 5;
			break;
		case 'd':
		case 'D':
			cx += 5;
			break;

		}

		if (cy < 0) cy = 0;
		if (cy > img->height - 5) cy = img->height - 5;
		if (cx < 0) cx = 0;
		if (cx > img->width - 5) cx = img->width - 5;

		write(dev, NULL, 1);
		read(dev, rgb, CIS_IMAGE_SIZE);
		RGB2cvIMG(img, rgb, 320, 240);


		if (ch == ' ') break;

		for (y = 0; y < img->height; y++)
			cvSet2D(img, y, cx, CV_RGB(80, 255, 80));
		for (x = 0; x < img->width; x++)
			cvSet2D(img, cy, x, CV_RGB(80, 255, 80));

		fb_display_IplImage(img, 240, 120);
	}
	// 평균내는 부분
	for (y = -2; y <= 2; y++) // 각 축 샘플 수
	for (x = -2; x <= 2; x++)
	{
		tmp_r += (rgb[(cy + y) * 320 + (cx + x)] >> 8) & 0xf8;
		tmp_g += (rgb[(cy + y) * 320 + (cx + x)] >> 3) & 0xfc;
		tmp_b += (rgb[(cy + y) * 320 + (cx + x)] << 3) & 0xf8;
	}

	*r = tmp_r / 25; // 샘플수로 나누어 평균 구함
	*g = tmp_g / 25;
	*b = tmp_b / 25;

	printf("\n point(%d,%d)`s Color = 0x%x", cx, cy, rgb[cy * 320 + cx]);

	cvCvtColor(img, img, CV_BGR2YCrCb);
	CvScalar s;
	s = cvGet2D(img, cy, cx);
	Y1 = (BYTE)(s.val[0]); //y
	Cr = (BYTE)(s.val[1]); //cr
	Cb = (BYTE)(s.val[2]); //cb	

	/* 기본 오차 상수는 전부 20 */

	col.Y_min = Y1 - 40; // 명도 성분
	col.Y_max = Y1 + 40;
	col.Cr_min = Cr - 20; // 색차 성분
	col.Cr_max = Cr + 20;
	col.Cb_min = Cb - 20;
	col.Cb_max = Cb + 20;

	printf("\n %d,%d,%d\n", Y1, Cr, Cb);
	return col;
}



