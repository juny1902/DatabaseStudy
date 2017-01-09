// Pointer2_Array.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

