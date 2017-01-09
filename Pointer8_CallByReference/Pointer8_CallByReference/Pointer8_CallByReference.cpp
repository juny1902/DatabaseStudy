// Pointer8_CallByReference.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
using namespace std;
void Square(int, int *);
void Square(int lv, int *ret) // 2. 포인터를 넘겨받는 매개 변수
{
	if (lv == 2) {
		*ret *= *ret; // 3. 주소의 값을 직접 연산.
	}
	else if (lv == 3) {
		*ret = *ret * *ret * *ret;
	}
}
int main()
{
	int number, level;
	level = 2;
	number = 3;
	Square(level,&number); // 1.number 변수의 주소를 Square 함수의 매개변수로 넘김.
	cout << level << "\t" << number << endl;
	level = 3;
	number = 4;
	Square(level, &number);
	cout << level << "\t" << number << endl;
	/* call by reference : 주소값을 참조하여 직접 값에 접근함. 매개변수를 일반 변수 대신 포인터로 사용.*/
	_getch();
    return 0;
}

