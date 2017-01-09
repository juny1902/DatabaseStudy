// Pointer7_operator.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
using namespace std;
int main()
{
	char buf[6] = { 'a','b','c','d','e','f' };
	char *ptr = buf;
	int i = 0;

	cout << "ptr을 1씩 증가시켜보자" << endl;

	for (i = 0; i < 6; i++) {
		cout << hex << (int)ptr << "\t" << *ptr << endl;
		ptr++;
	}
	cout << "ptr이 다시 buf 를 가리킴" << endl;
	ptr = buf;

	cout << "*ptr++ 의 결과" << endl;
	cout << hex << (int)ptr << "\t" << *ptr++ << endl;

	cout << "*(ptr++) 의 결과" << endl;
	cout << hex << (int)ptr << "\t" << *(ptr++) << endl;

	cout << "--ptr을 한 후 *(ptr++)의 결과" << endl;
	--ptr;
	cout << hex << (int)ptr << "\t" << *(ptr++) << endl;

	cout << "(*ptr)++ 의 결과" << endl;
	(*ptr)++;
	cout << hex << (int)ptr << "\t" << *ptr << endl;

	cout << "ptr += 1 한후 *ptr의 결과" << endl;
	ptr += 1;
	cout << hex << (int)ptr << "\t" << *ptr << endl;

	cout << "ptr -=2 한후 *ptr의 결과" << endl;
	ptr -= 2;
	cout << hex << (int)ptr << "\t" << *ptr << endl;

	_getch();

	return 0;
}

