/*
	스택 : 입/출력을 한 방향으로 제한한 자료구조

	푸시 : 데이터를 쌓음
	팝 : 쌓은 데이터를 하나 꺼냄


	후입선출 (LIFO) : 마지막으로 들어간것이 먼저 나옴
*/

#include "stdafx.h"
#include <iostream>
#include <conio.h>
using namespace std;

void InitializeStack(void);
void PUSH(int num);
void DisplayStack(void);

typedef struct _NODE {
	int Data;
	struct _NODE *Next;
} NODE;
NODE *head, *tail;
NODE *ptrNode;

void InitializeStack(void)
{
	head = (NODE *)malloc(sizeof(NODE));
	tail = (NODE *)malloc(sizeof(NODE));
	head->Next = tail;
	tail->Next = tail;
}
void PUSH(int num)
{
	ptrNode = (NODE *)malloc(sizeof(NODE));
	ptrNode->Data = num;
	ptrNode->Next = head->Next;
	head->Next = ptrNode;
}
int POP(void)
{
	int ret;
	ptrNode = head->Next;
	head->Next = head->Next->Next;
	ret = ptrNode->Data;

	free(ptrNode);
	return ret;
}
void DisplayStack(void)
{
	NODE *indexNode;
	cout << "Head(TOP) -> ";
	for (indexNode = head->Next; indexNode != tail; indexNode = indexNode->Next) {
		cout << indexNode->Data << " -> ";
	}
	cout << "Tail(BOTTOM)" << endl;
}
int main()
{
	int ret, n;
	InitializeStack();
	cout << "값을 입력하세요 (0 = 입력종료)" << endl;
	do {
		cin >> n;
		if (n != 0) PUSH(n);
	} while (n);

	DisplayStack();

	cout << "엔터 하면 하나씩 뺄거야" << endl;
	while (_getch() != 0) {
		if (head->Next == tail) break;
		ret = POP();
		cout << "뺀 값 : " << ret << endl;
		DisplayStack();

	}
	cout << "데이터 모두 소진 !" << endl;
	_getch();
	return 0;
}

