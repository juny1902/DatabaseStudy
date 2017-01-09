// Array_2D.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#define STUDENT 5
#define SUBJECT 2
using namespace std;

int score[STUDENT][SUBJECT];
void DisplayTable(void)
{
	int i;
	int Total[2] = { 0,0 };
	cout << "번호\t영어\t수학\t평균" << endl;
	for (i = 0; i < STUDENT; i++) {
		cout << i << "\t" << score[i][0] << "\t" << score[i][1] << "\t" << (double)(score[i][0] + score[i][1]) / (double)SUBJECT << endl;
		Total[0] += score[i][0];
		Total[1] += score[i][1];
	}
	cout << "-------------------------------------" << endl;
	cout << "총점\t" << Total[0] << "\t" << Total[1] << "\t" << endl;
	cout << "평균\t" << (double)(Total[0] / STUDENT) << "\t" << (double)(Total[1] / STUDENT) << "\t" << endl;
}
int main()
{
	int n = 0;

	cout << "학생 별 점수 입력." << endl;
	for (n = 0; n < STUDENT; n++) {
		cout << n+1 << "번 학생의 영어 점수 = ";
		cin >> score[n][0];
		cout << n+1 << "번 학생의 수학 점수 = ";
		cin >> score[n][1];
	}
	cout << "입력 끝 !" << endl;
	DisplayTable();
	cin >> n;
	return 0;
}

