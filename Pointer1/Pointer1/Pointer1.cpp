// Pointer1.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
int main()
{
	int data = 10; // int�� ���� ����
	int *ptr; // ������ ���� ����

	cout << "data �� �ּ� = " << &data << ", data �� �� = " << data << endl;
	ptr = &data; // ������ = int�� ������ �ּ�

	cout << "ptr �� �ּ� = " << &ptr << ", ptr�� �� = " << ptr << endl; // ptr�� �� = data�� �ּ�

	cout << "ptr�� ����Ű�� ���� �� = " << *ptr << ", data�� �� = " << data << endl; // ptr�� ����Ű�� ���� �� = data�� ��

	cout << "ptr�� �ּ� = " << &ptr << ", ptr�� �� = " << ptr << ", ptr�� ����Ű�� ���� �� =" << *ptr << endl;

	/* 
		��� : ������ ������ ������ �ּҸ� �����Ѵ�. *ptr = ����Ű�� ���� ��, &ptr = ������ ���� ��ü�� �ּ�, ptr = ����Ű�� �ּ�
	*/

	cin >> data;

    return 0;
}

