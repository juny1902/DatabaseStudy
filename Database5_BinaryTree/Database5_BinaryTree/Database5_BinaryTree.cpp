/*
	���� Ʈ�� : �ڽ� ��尡 2���� ����.

	���� ����Ʈ�� : ��� ��忡 �ڽ� ��尡 �ϳ��� ���ų� 2���� �ڽ� ��带 ����. (�ڽ� ��带 �ϳ��� ���� ��찡 ����)
	�� ���� Ʈ�� : ���� ����Ʈ���̰� ���� ������ ������ ���� (��Ī)

	��ȸ �˰��� (���� ���� �� ���� �湮�Ѵ�.)
	1.���� ��ȸ
	2.���� ��ȸ
	3.���� ��ȸ
	4.�ܰ� ��ȸ

*/
#include "stdafx.h"
#include "node.h"
// externs
extern void InitializeStack(void);
extern void Push(Node *);
extern Node *Pop(void);
extern int IsStackEmpty(void);

// interns
void InitializeTree(void);
void MakeTree(void);
void Traverse(Node *);
void Visit(Node *);

// Variables
Node *Parent, *LeftChild, *RightChild;
Node *HeadNode, *EndNode;

void InitializeTree(void)
{
	HeadNode = (Node *)malloc(sizeof(Node));
	EndNode = (Node *)malloc(sizeof(Node));

	HeadNode->Left = EndNode;
	HeadNode->Right = EndNode;
	EndNode->Left = EndNode;
	EndNode->Right = EndNode;
}

void MakeTree(void)
{
	Parent = (Node *)malloc(sizeof(Node));
	Parent->Data = 'A';

	LeftChild = (Node *)malloc(sizeof(Node));
	LeftChild->Data = 'B';

	RightChild = (Node *)malloc(sizeof(Node));
	RightChild->Data = 'C';

	Parent->Left = LeftChild;
	Parent->Right = RightChild;

	HeadNode->Left = Parent; // LeftChild �� �߸� ����
	HeadNode->Right = Parent; // RightChild �� �߸� ����

	Parent = Parent->Left;

	LeftChild = (Node *)malloc(sizeof(Node));
	LeftChild->Data = 'D';
	LeftChild->Left = EndNode;
	LeftChild->Right = EndNode;

	RightChild = (Node *)malloc(sizeof(Node));
	RightChild->Data = 'E';
	RightChild->Left = EndNode;
	RightChild->Right = EndNode;

	Parent->Left = LeftChild;
	Parent->Right = RightChild;
	Parent = HeadNode->Right->Right;

	LeftChild = (Node *)malloc(sizeof(Node));
	LeftChild->Data = 'F';
	LeftChild->Left = EndNode;
	LeftChild->Right = EndNode;

	RightChild = (Node *)malloc(sizeof(Node));
	RightChild->Data = 'G';
	RightChild->Left = EndNode;
	RightChild->Right = EndNode;

	Parent->Left = LeftChild;
	Parent->Right = RightChild;
}

void Traverse(Node *ptrNode)
{
	Push(ptrNode);

	while (!IsStackEmpty()) {
		ptrNode = Pop();
		Visit(ptrNode);

		if (ptrNode->Right != EndNode) Push(ptrNode->Right);

		if (ptrNode->Left != EndNode) Push(ptrNode->Left);
	}
}
void Visit(Node *ptrNode)
{
	cout << ptrNode->Data << " -> ";
}
int main()
{
	InitializeStack();
	InitializeTree();
	MakeTree();
	Traverse(HeadNode->Left);
	_getch();
	return 0;
}

