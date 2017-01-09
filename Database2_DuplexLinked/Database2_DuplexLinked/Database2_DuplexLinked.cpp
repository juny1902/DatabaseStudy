/*

	이중 링크드 리스트 : 단일 링크드 리스트의 단점 보완, 단일 링크드 리스트에서 이전 노드 지시하는 변수 추가.

	삽입
		1. 단일 링크드 리스트와 비슷함.

	삭제
		1. 이전 노드, 삭제할 노드를 가리킬 포인터 선언
		2. 삭제할 노드를 검색한다.
		3. 이전 노드가 삭제할 노드를 건더뛰고 다음 노드를 가리키도록 링크 설정
		4. free() 함수로 메모리 할당 해제

	원형 링크드 리스트 : 이중 링크드 리스트의 헤드와 테일을 이어 원형으로 구성.

*/

#include "stdafx.h"
#include <iostream>
#include <conio.h>
using namespace std;

typedef struct _NODE {
	char Data;
	struct _NODE *Next;
	struct _NODE *Prev;
} NODE;

NODE *head, *tail, *temp;
NODE *temp1, *temp2, *temp3, *temp4;

void Initalize(void);
void InsertNode(NODE *ptr);
void DeleteNode(NODE *ptr);

void Initalize(void)
{
	NODE *ptr;
	head = (NODE *)malloc(sizeof(NODE));
	tail = (NODE *)malloc(sizeof(NODE));

	temp1 = (NODE *)malloc(sizeof(NODE));
	temp1->Data = 'A';
	head->Next = temp1;
	temp1->Next = tail;
	temp1->Prev = head;
	tail->Next = tail;
	ptr = temp1;

	temp2 = (NODE *)malloc(sizeof(NODE));
	temp2->Data = 'B';
	ptr->Next = temp2;
	temp2->Next = tail;
	temp2->Prev = ptr;
	ptr = temp2;

	temp3 = (NODE *)malloc(sizeof(NODE));
	temp3->Data = 'D';
	ptr->Next = temp3;
	temp3->Next = tail;
	temp3->Prev = ptr;
	ptr = temp3;

	temp4 = (NODE *)malloc(sizeof(NODE));
	temp4->Data = 'E';
	ptr->Next = temp4;
	temp4->Next = tail;
	temp4->Prev = ptr;
	ptr = temp4;
}
void InsertNode(NODE *ptr)
{
	NODE *indexptr;
	for (indexptr = head->Next; indexptr != tail; indexptr = indexptr->Next) { // 노드의 처음부터 끝까지...
		if (indexptr->Data < ptr->Data && indexptr->Next->Data > ptr->Data) break; // 삽입할 위치(indexptr)를 찾음,
		// 삽입할 노드의 값이 어느 위치의 값보다 크고, 삽입할 위치의 다음 노드가 삽입할 노드의 값보다 커야한다. (중간 위치) 
	}

	ptr->Next = indexptr->Next;
	indexptr->Next->Prev = ptr; // 삽입할 위치의 다음 노드의 이전 노드를 삽입할 노드로 설정.
	indexptr->Next = ptr;
	ptr->Prev = indexptr;
}
void DeleteNode(NODE *ptr)
{
	NODE *indexptr;
	NODE *deleteptr;
	for (indexptr = head; indexptr != tail; indexptr = indexptr->Next) { // 노드의 처음부터 끝까지...
		if (indexptr->Next->Data == ptr->Data) { // 어느 지점의 다음 노드 = 삭제할 노드 ?
			deleteptr = indexptr->Next; // 삭제할 노드를 저장해두고...
			break;
		}
	}
	indexptr->Next = indexptr->Next->Next; // 삭제할 노드의 다음노드를 앞으로 당기고
	indexptr->Next->Next->Prev = indexptr; // 삭제할 노드의 다음노드의 이전 노드를 재설정. *재검토 필요
}
int main()
{
	NODE *ptr;
	int i = 0;
	Initalize();

	cout << "노드 C 삽입 전" << endl;
	ptr = head->Next;

	for (i = 0; i < 4; i++) {
		cout << ptr->Data;
		ptr = ptr->Next;
	}

	temp = (NODE *)malloc(sizeof(NODE));
	temp->Data = 'C';

	InsertNode(temp);

	cout << endl << "노드 C 삽입 후" << endl;
	ptr = head->Next;

	for (i = 0; i < 5; i++) {
		cout << ptr->Data;
		ptr = ptr->Next;
	}

	DeleteNode(temp);

	cout << endl << "노드 C 삭제 후" << endl;
	ptr = head->Next;

	for (i = 0; i < 4; i++) {
		cout << ptr->Data;
		ptr = ptr->Next;
	}

	_getch();

	return 0;
}

