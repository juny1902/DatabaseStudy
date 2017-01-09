/*
	���� : ��/����� �� �������� ������ �ڷᱸ��

	Ǫ�� : �����͸� ����
	�� : ���� �����͸� �ϳ� ����


	���Լ��� (LIFO) : ���������� ������ ���� ����
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
	cout << "���� �Է��ϼ��� (0 = �Է�����)" << endl;
	do {
		cin >> n;
		if (n != 0) PUSH(n);
	} while (n);

	DisplayStack();

	cout << "���� �ϸ� �ϳ��� ���ž�" << endl;
	while (_getch() != 0) {
		if (head->Next == tail) break;
		ret = POP();
		cout << "�� �� : " << ret << endl;
		DisplayStack();

	}
	cout << "������ ��� ���� !" << endl;
	_getch();
	return 0;
}

