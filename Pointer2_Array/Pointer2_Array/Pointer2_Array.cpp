// Pointer2_Array.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int data[5] = { 10,20,30,40,50 };
	int *ptr;
	ptr = data;
	cout << "ptr=" << ptr << ", *ptr=" << *ptr << endl;

	ptr = &data[0];
	cout << "ptr=" << ptr << ", *ptr=" << *ptr << endl;

	cin >> data[0];
    return 0;
}

