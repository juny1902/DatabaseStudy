// Pointer6_calc.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
using namespace std;

int main()
{
	int i;
	int data[][2] = { {10,20},{30,40},{50,60},{70,80},{90,100} };
	int(*ptr)[2]; // 포인터의 크기(2열)를 지정해주어야함. (Pointer5 참조)
	int *tptr[5];
	ptr = data; // 포인터 변수 ptr의 값은 data 배열의 [0][0] 주소.

	tptr[0] = &data[0][0]; // 포인터 배열 tptr[0] 의 값은, data[0][0] 의 주소
	tptr[1] = &data[1][0];
	tptr[2] = &data[2][0];
	tptr[3] = &data[3][0];
	tptr[4] = &data[4][0];

	for (i = 0; i < 5; i++) {
		cout << ptr << "\t" << **ptr << "\t" << *(*ptr + 1) << endl; // 포인터 주소, 주소의 값, (주소+1)의 값
		ptr++;
	}
	for (i = 0; i < 5; i++) {
		cout << tptr[i] << "\t" << *tptr[i] << "\t" << *(tptr[i] + 1) << endl; // 포인터 배열 원소, 그 원소의 값, 원소 +1의 값.
	}
	// 주소는 완전히 같음(data의 주소를 참조)

	// ptr + 1 은 주소 + 1 이 아닌, 메모리 크기 기준단위를 더함 (int = 4, double = 8 char = 1 ... 등등)
	_getch();

	return 0;
}

