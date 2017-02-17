#include "stdafx.h"
#include "node.h"

#define MAX 100
Node *Stack[MAX]; // 스택을 배열로 선언
int Top;

void InitializeStack(void);
void Push(Node *);
Node *Pop(void);
int IsStackEmpty(void);

void InitializeStack(void)
{
	Top = 0;
}

void Push(Node *ptrNode)
{
	Stack[Top] = ptrNode;
	Top = (Top++) % MAX;
}

Node *Pop(void)
{
	Node *ptrNode;

	if (!IsStackEmpty()) {
		ptrNode = Stack[--Top];
		return ptrNode;
	}
	else {
		cout << "Stack is empty." << endl;
		return NULL;
	}
}
int IsStackEmpty(void)
{
	if (Top == 0)
		return true;
	else 
		return false;
}
