// Pointer7_operator.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

	cout << "ptr�� 1�� �������Ѻ���" << endl;

	for (i = 0; i < 6; i++) {
		cout << hex << (int)ptr << "\t" << *ptr << endl;
		ptr++;
	}
	cout << "ptr�� �ٽ� buf �� ����Ŵ" << endl;
	ptr = buf;

	cout << "*ptr++ �� ���" << endl;
	cout << hex << (int)ptr << "\t" << *ptr++ << endl;

	cout << "*(ptr++) �� ���" << endl;
	cout << hex << (int)ptr << "\t" << *(ptr++) << endl;

	cout << "--ptr�� �� �� *(ptr++)�� ���" << endl;
	--ptr;
	cout << hex << (int)ptr << "\t" << *(ptr++) << endl;

	cout << "(*ptr)++ �� ���" << endl;
	(*ptr)++;
	cout << hex << (int)ptr << "\t" << *ptr << endl;

	cout << "ptr += 1 ���� *ptr�� ���" << endl;
	ptr += 1;
	cout << hex << (int)ptr << "\t" << *ptr << endl;

	cout << "ptr -=2 ���� *ptr�� ���" << endl;
	ptr -= 2;
	cout << hex << (int)ptr << "\t" << *ptr << endl;

	_getch();

	return 0;
}

