// Pointer5_asParameter.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
using namespace std;
void PrintPointer(int(*)[2]); // ���� �� �� �迭�� ũ�⸦ �� �� �ְ� �ؾ���. (2��)
void PrintPointer(int(*tptr)[2])
{
	int i;
	cout << "�Լ� ȣ���" << endl;
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
	cout << "�Լ� ȣ�� ��" << endl;

	for (i = 0; i < 5; i++) {
		cout << ptr << "\t" << **ptr << endl;
		ptr++;
	}
	ptr = data;
	PrintPointer(ptr); // �޸� �ּҰ��� �״�� �Լ��� ����, ������ ���� �޸� �ּҸ� ����.
	_getch();
    return 0;
}

