// Pointer8_CallByReference.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
using namespace std;
void Square(int, int *);
void Square(int lv, int *ret) // 2. �����͸� �Ѱܹ޴� �Ű� ����
{
	if (lv == 2) {
		*ret *= *ret; // 3. �ּ��� ���� ���� ����.
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
	Square(level,&number); // 1.number ������ �ּҸ� Square �Լ��� �Ű������� �ѱ�.
	cout << level << "\t" << number << endl;
	level = 3;
	number = 4;
	Square(level, &number);
	cout << level << "\t" << number << endl;
	/* call by reference : �ּҰ��� �����Ͽ� ���� ���� ������. �Ű������� �Ϲ� ���� ��� �����ͷ� ���.*/
	_getch();
    return 0;
}

