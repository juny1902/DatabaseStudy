/*

	큐 : 스택의 반대개념, 선입선출 (FIFO) (배열 사용하는게 좀 더 편함)

	Put : 데이터 저장, Get : 데이터 사용

*/

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#define MAX 100
using namespace std;
int queue[MAX];
int front, rear;

void InitalizeQueue(void);
void Put(int);
int Get(void);
void DisplayQueue(void);

void InitalizeQueue(void)
{
	front = rear = 0;
}
void Put(int num)
{
	queue[rear++] = num;

	if (rear >= MAX)
		rear = 0;
}
int get(void)
{
	int ret;
	ret = queue[front++];

	if (front >= MAX) front = 0;
	return ret;
}
void DisplayQueue(void)
{
	int i;
	cout << "Front -> ";
	for (i = front; i < rear; i++) {
		cout << queue[i] << " -> ";
	}
	cout << "Rear" << endl;
}
int main()
{
	int ret, num = 1;
	InitalizeQueue();
	while (num) {
		cin >> num;
		if (num != 0) Put(num);
	}
	DisplayQueue();


	do {
		ret = get();
		if (ret == 0) break;
		cout << "뺀 값 : " << ret << endl;
		DisplayQueue();
	} while (_getch());

	cout << "데이터 모두 소진" << endl;
	_getch();
	return 0;
}

