// Pointer6_calc.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
using namespace std;

int main()
{
	int i;
	int data[][2] = { {10,20},{30,40},{50,60},{70,80},{90,100} };
	int(*ptr)[2]; // �������� ũ��(2��)�� �������־����. (Pointer5 ����)
	int *tptr[5];
	ptr = data; // ������ ���� ptr�� ���� data �迭�� [0][0] �ּ�.

	tptr[0] = &data[0][0]; // ������ �迭 tptr[0] �� ����, data[0][0] �� �ּ�
	tptr[1] = &data[1][0];
	tptr[2] = &data[2][0];
	tptr[3] = &data[3][0];
	tptr[4] = &data[4][0];

	for (i = 0; i < 5; i++) {
		cout << ptr << "\t" << **ptr << "\t" << *(*ptr + 1) << endl; // ������ �ּ�, �ּ��� ��, (�ּ�+1)�� ��
		ptr++;
	}
	for (i = 0; i < 5; i++) {
		cout << tptr[i] << "\t" << *tptr[i] << "\t" << *(tptr[i] + 1) << endl; // ������ �迭 ����, �� ������ ��, ���� +1�� ��.
	}
	// �ּҴ� ������ ����(data�� �ּҸ� ����)

	// ptr + 1 �� �ּ� + 1 �� �ƴ�, �޸� ũ�� ���ش����� ���� (int = 4, double = 8 char = 1 ... ���)
	_getch();

	return 0;
}

