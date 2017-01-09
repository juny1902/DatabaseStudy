/*

	단일 링크드 리스트

	1.노드(객차)와 링크(쇠사슬)로 구성됨 -->  ㅁ-ㅁ-ㅁ-ㅁ-ㅁ
	2.노드의 맨 앞에는 헤드노드, 끝에는 테일노드가 위치. 데이터를 저장하지 않음. --> (헤드) - A - B - C - D - (테일)
	3.링크드 리스트의 기본 구조 : (헤드) -> A -> B -> C -> D -> (테일)
	ㄴ 단일 링크드 리스트 : 자신의 노드에서 다음 노드만을 가리킬 수 있는 형태.

	배열과의 차이점
	1.배열 = 연속된 메모리 사용. 정렬시 복잡함
	2.리스트 = 반드시 연속적이진 않음
	2.연속적이지 않은 데이터를 서로 연결하는 개념

	주요 알고리즘
	1.노드 삽입 ex) (헤드) -> A -> B -> ㅇ -> D -> E -> (테일)
		ㄴ 1. 새로운 노드 생성
		ㄴ 2. 새로운 노드가 삽입될 위치를 검색
		ㄴ 3. 새로운 노드가 삽입될 위치의 다음 노드와 연결(C -> D)
		ㄴ 4. 삽입될 위치의 이전 노드를 새로운 노드에 연결(B -> C)
	2.노드 삭제
		ㄴ 1. 이전 노드와 삭제할 노드를 가리킬 포인터 선언
		ㄴ 2. 삭제할 노드 검색
		ㄴ 3. 이전 노드가 삭제할 노드를 건너 뛰고 다음 노드를 가리키도록 링크 설정.
		ㄴ 4. 삭제할 노드의 메모리 할당 해제

*/


#include "stdafx.h"
#include <iostream>
#include <conio.h>
using namespace std;

#define ARRAY_VER 0
#define NODE_VER 1

#if ARRAY_VER
char Data[5] = { 'A','B','D','E' };
char c;
int main()
{
	cout << "데이터 삽입 알고리즘 (배열 이용)" << endl;
	int i, temp1, temp2;
	c = 'C';

	for (i = 0; i < 5; i++) {
		cout << Data[i] << "\t";
	}

	for (i = 0; i < 5; i++) {
		if (Data[i] > c) break; // Data[i]가 c보다 큰 값을 만날때의 i값을 얻어냄.
	}
	temp1 = Data[i]; // Data[i] 의 값을 임시저장.
	Data[i] = c; // Data[i] 에 c를 덮어 씌움.
	i++;

	for (; i < 5; i++) {
		temp2 = Data[i];
		Data[i] = temp1; // 배열의 단점, 임시값을 이용하여 뒤의 값을 밀어줘야 함. 100
		temp1 = temp2;
	}

	cout << endl << "삽입 완료" << endl;
	for (i = 0; i < 5; i++) {
		cout << Data[i] << "\t";
	}
	_getch();
	return 0;
}
#endif // ARRAY_VER
#if NODE_VER
typedef struct _NODE {
	char Data; // 노드의 값이 저장되는 곳
	struct _NODE *Next; // 노드가 가리키는 곳.
} NODE;

NODE *head, *tail, *temp;
NODE *temp1, *temp2, *temp3, *temp4;

void Initialize(void);
void InsertNode(NODE *);
void DeleteNode(NODE *);
void Initialize(void)
{
	NODE *ptr;
	head = (NODE *)malloc(sizeof(NODE)); // NODE의 크기만큼 메모리 동적 할당.
	tail = (NODE *)malloc(sizeof(NODE));

	temp1 = (NODE *)malloc(sizeof(NODE));
	temp1->Data = 'A'; // temp1 구조체 변수의 Data 항목의 값은 'A'
	head->Next = temp1; // 헤드의 다음 노드는 'A' (temp1)
	temp1->Next = tail; // 'A' (temp1)의 다음 노드는 '끝'
	tail->Next = tail; // 끝의 다음 노드는 '끝'
	ptr = temp1; // 현재 포인터는 temp1

	temp2 = (NODE *)malloc(sizeof(NODE));
	temp2->Data = 'B';
	ptr->Next = temp2;
	temp2->Next = tail;
	ptr = temp2;

	temp3 = (NODE *)malloc(sizeof(NODE));
	temp3->Data = 'D';
	ptr->Next = temp3;
	temp3->Next = tail;
	ptr = temp3;

	temp4 = (NODE *)malloc(sizeof(NODE));
	temp4->Data = 'E';
	ptr->Next = temp4;
	temp4->Next = tail;
	ptr = temp4;
}

void InsertNode(NODE *ptr)
{
	NODE *indexptr;
	for (indexptr = head; indexptr != tail; indexptr = indexptr->Next) { // 인덱스는 헤드부터 테일까지 노드 하나씩 건너뛰며 루프
		if (indexptr->Next->Data > ptr->Data) break; // 어느 노드의 다음 데이터가 현재 데이터보다 크면 탈출 (인덱스 포인터 값을 가진채로)
	}

	ptr->Next = indexptr->Next; // 삽입할 노드(ptr) 의 다음 노드를 삽입될 위치(indexptr) 의 다음 노드에 연결
	indexptr->Next = ptr; // 삽입할 노드의 이전 노드를 삽입할 노드로 설정
}
void DeleteNode(NODE *ptr)
{
	NODE *indexptr; // 이전 노드를 가리킬 포인터
	NODE *deleteptr=0; // 삭제할 노드를 가리킬 포인터
	for (indexptr = head; indexptr != tail; indexptr = indexptr->Next) {
		if (indexptr->Next->Data == ptr->Data) {
			deleteptr = indexptr->Next; // 제거할 노드는 인덱스 포인터의 다음 노드 
			break;
		}
	}
	indexptr->Next = indexptr->Next->Next; // 제거할 데이터의 이전 노드를 제거할 데이터의 다음 노드와 연결
	

}
void main()
{
	NODE *ptr;
	int i = 0;
	Initialize();
	ptr = head->Next; // 포인터의 위치는 첫번째 노드 (헤드 다음)
	cout << "정렬 전 : ";
	for (i = 0; i < 4; i++) {
		cout << ptr->Data; // 노드의 데이터를 출력
		ptr = ptr->Next; // 다음 노드로 이동.
	}

	temp = (NODE *)malloc(sizeof(NODE));
	temp->Data = 'C';
	InsertNode(temp);

	ptr = head->Next; // 포인터의 위치는 첫번째 노드 (헤드 다음)
	cout << endl << "정렬 후 : ";
	for (i = 0; i < 5; i++) {
		cout << ptr->Data; // 노드의 데이터를 출력
		ptr = ptr->Next; // 다음 노드로 이동.
	}

	DeleteNode(temp);
	ptr = head->Next; // 포인터의 위치는 첫번째 노드 (헤드 다음)
	cout << endl << "삭제 후 : ";
	for (i = 0; i < 5; i++) {
		cout << ptr->Data; // 노드의 데이터를 출력
		ptr = ptr->Next; // 다음 노드로 이동.
	}
	_getch();

}


#endif // NODE_VER
