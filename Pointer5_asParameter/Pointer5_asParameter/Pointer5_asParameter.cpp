// Pointer5_asParameter.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
using namespace std;
void PrintPointer(int(*)[2]); // 정의 할 때 배열의 크기를 알 수 있게 해야함. (2열)
void PrintPointer(int(*tptr)[2])
{
	int i;
	cout << "함수 호출부" << endl;
	for (i = 0; i < 5; i++) {
		cout << tptr << "\t" << **tptr << endl;
		tptr++;
	}
}
int main()
{
	int i;
	int data[][2] = { {10, 20}, { 30,40 }, { 50,60 }, { 70,80 }, { 90,100 } };
	int(*ptr)[2];
	ptr = data;
	cout << "함수 호출 전" << endl;

	for (i = 0; i < 5; i++) {
		cout << ptr << "\t" << **ptr << endl;
		ptr++;
	}
	ptr = data;
	PrintPointer(ptr); // 메모리 주소값을 그대로 함수에 전달, 완전히 같은 메모리 주소를 가짐.
	_getch();
    return 0;
}

