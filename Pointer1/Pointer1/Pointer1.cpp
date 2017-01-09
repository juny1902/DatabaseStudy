// Pointer1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
int main()
{
	int data = 10; // int형 변수 선언
	int *ptr; // 포인터 변수 선언

	cout << "data 의 주소 = " << &data << ", data 의 값 = " << data << endl;
	ptr = &data; // 포인터 = int형 변수의 주소

	cout << "ptr 의 주소 = " << &ptr << ", ptr의 값 = " << ptr << endl; // ptr의 값 = data의 주소

	cout << "ptr이 가리키는 곳의 값 = " << *ptr << ", data의 값 = " << data << endl; // ptr이 가리키는 곳의 값 = data의 값

	cout << "ptr의 주소 = " << &ptr << ", ptr의 값 = " << ptr << ", ptr이 가리키는 곳의 값 =" << *ptr << endl;

	/* 
		결론 : 포인터 변수는 변수의 주소를 저장한다. *ptr = 가리키는 곳의 값, &ptr = 포인터 변수 자체의 주소, ptr = 가리키는 주소
	*/

	cin >> data;

    return 0;
}

