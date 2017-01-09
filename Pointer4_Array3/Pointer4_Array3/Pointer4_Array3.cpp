// Pointer4_Array3.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>
using namespace std;

int main()
{
	int data[5] = { 10,20,30,40,50 };
	int *ptr = data; // data 배열의 주소 (배열 이름을 포인터에 할당)
	int i;
	cout << *ptr << "\t" << ptr << endl;
	ptr = &data[0]; // data 배열의 0번 원소의 주소 (배열의 첫 원소를 포인터에 할당)
	cout << *ptr << "\t" << ptr << endl << endl;
	_getch();

	for (i = 0; i < 5; i++) {
		cout << *ptr << "\t" << ptr << endl; // 주소에 있는 값과 주소
		ptr++; // 다음 원소의 주소로
	}
	for (i = 0; i < 5; i++) {
		cout << data[i] << "\t" << &data[i] << endl; // 각 원소의 값과 그 주소
	}
	
	/*	
		포인터 변수에 ++ 연산을 하면 지시하는 메모리 주소가 달라지므로 유의해야함.
		반면 배열은 인덱스에 직접 지시하므로 그렇지 않음.
	*/
	_getch();

    return 0;
}

