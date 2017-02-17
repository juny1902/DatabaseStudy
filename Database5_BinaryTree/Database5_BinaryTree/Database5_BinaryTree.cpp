/*
	이진 트리 : 자식 노드가 2개만 있음.

	완전 이진트리 : 모든 노드에 자식 노드가 하나도 없거나 2개의 자식 노드를 가짐. (자식 노드를 하나만 갖는 경우가 없음)
	정 이진 트리 : 완전 이진트리이고 리프 노드들의 레벨이 같음 (대칭)

	순회 알고리즘 (노드는 오직 한 번만 방문한다.)
	1.전위 순회
	2.중위 순회
	3.후위 순회
	4.단계 순회

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

	HeadNode->Left = Parent; // LeftChild 로 잘못 기재
	HeadNode->Right = Parent; // RightChild 로 잘못 기재

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

