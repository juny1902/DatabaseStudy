// Pointer4_Array3.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>
using namespace std;

int main()
{
	int data[5] = { 10,20,30,40,50 };
	int *ptr = data; // data �迭�� �ּ� (�迭 �̸��� �����Ϳ� �Ҵ�)
	int i;
	cout << *ptr << "\t" << ptr << endl;
	ptr = &data[0]; // data �迭�� 0�� ������ �ּ� (�迭�� ù ���Ҹ� �����Ϳ� �Ҵ�)
	cout << *ptr << "\t" << ptr << endl << endl;
	_getch();

	for (i = 0; i < 5; i++) {
		cout << *ptr << "\t" << ptr << endl; // �ּҿ� �ִ� ���� �ּ�
		ptr++; // ���� ������ �ּҷ�
	}
	for (i = 0; i < 5; i++) {
		cout << data[i] << "\t" << &data[i] << endl; // �� ������ ���� �� �ּ�
	}
	
	/*	
		������ ������ ++ ������ �ϸ� �����ϴ� �޸� �ּҰ� �޶����Ƿ� �����ؾ���.
		�ݸ� �迭�� �ε����� ���� �����ϹǷ� �׷��� ����.
	*/
	_getch();

    return 0;
}

