// Array_firstD.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#define MAX_ELEMENT 100
#define Sentinel 0
#define TRUE 1
#define FALSE 0
using namespace std;
int GetIntegerArray(int array[], int max, int sentinel);
int GetInteger(void);
void PrintIntegerArray(int array[], int n);
void ReverseIntegerArray(int array[], int n);
void SwapIntegerElements(int array[], int p1, int p2);
int GetIntegerArray(int array[], int max, int sentinel) // 배열과 최대값을 입력받아 각 원소에 값을 대입하고 배열의 크기를 반환.
{
	int n, value;
	n = 0;
	while (TRUE) {
		cout << "==>" ;
		value = GetInteger(); // 정수값을 입력받음.
		if (value == sentinel) break; // 정수값 = 센티넬 이면 탈출.
		if (n == max) cout << "총 개수 초과함." << endl; // 배열의 현재 카운터와 목표 배열 크기가 같으면 ?
		array[n] = value; // 배열의 각 원소에 정수값 대입
		n++;
	}
	return n; // n (배열의 크기) 반환
}
int GetInteger(void) 
{
	int n;
	cin >> n; // n 입력받아서 반환.
	return n;
}
void PrintIntegerArray(int array[], int n) // n 크기의 array 입력받아서
{
	int i;
	for (i = 0; i < n; i++)
	{
		cout << array[i] << endl; // array[0]~[n] 까지 출력함 
	}
}
void ReverseIntegerArray(int array[], int n)
{
	int i;
	for (i = 0; i < n / 2; i++) // 배열의 크기의 절반 (중간 원소까지)
	{
		SwapIntegerElements(array, i, n - i - 1); // 배열(array), 현재 원소, 대칭되는 원소 (최대크기 - 현재 원소 - 1) 
	}
}
void SwapIntegerElements(int array[], int p1, int p2) // array 에서 p1 과 p2 를 교환함.
{
	int tmp;
	tmp = array[p1]; // p1 임시저장.
	
	array[p1] = array[p2]; // p2의 값을 p1에 덮어 씌움.
	array[p2] = tmp; // 임시저장된 p1 값을 p2에 덮어 씌움.
}
int main()
{
	int list[MAX_ELEMENT], n;

	cout << "임의의 정수값을 입력하세요." << endl << "0을 입력하면 입력 종료" << endl;
	n = GetIntegerArray(list, MAX_ELEMENT, Sentinel); // 배열 입력받기
	ReverseIntegerArray(list, n); // 배열 뒤집기
	PrintIntegerArray(list, n); // 배열 출력
	cin >> n;
    return 0;
}

