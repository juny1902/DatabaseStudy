/*

	���� ��ũ�� ����Ʈ : ���� ��ũ�� ����Ʈ�� ���� ����, ���� ��ũ�� ����Ʈ���� ���� ��� �����ϴ� ���� �߰�.

	����
		1. ���� ��ũ�� ����Ʈ�� �����.

	����
		1. ���� ���, ������ ��带 ����ų ������ ����
		2. ������ ��带 �˻��Ѵ�.
		3. ���� ��尡 ������ ��带 �Ǵ��ٰ� ���� ��带 ����Ű���� ��ũ ����
		4. free() �Լ��� �޸� �Ҵ� ����

	���� ��ũ�� ����Ʈ : ���� ��ũ�� ����Ʈ�� ���� ������ �̾� �������� ����.

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
	for (indexptr = head->Next; indexptr != tail; indexptr = indexptr->Next) { // ����� ó������ ������...
		if (indexptr->Data < ptr->Data && indexptr->Next->Data > ptr->Data) break; // ������ ��ġ(indexptr)�� ã��,
		// ������ ����� ���� ��� ��ġ�� ������ ũ��, ������ ��ġ�� ���� ��尡 ������ ����� ������ Ŀ���Ѵ�. (�߰� ��ġ) 
	}

	ptr->Next = indexptr->Next;
	indexptr->Next->Prev = ptr; // ������ ��ġ�� ���� ����� ���� ��带 ������ ���� ����.
	indexptr->Next = ptr;
	ptr->Prev = indexptr;
}
void DeleteNode(NODE *ptr)
{
	NODE *indexptr;
	NODE *deleteptr;
	for (indexptr = head; indexptr != tail; indexptr = indexptr->Next) { // ����� ó������ ������...
		if (indexptr->Next->Data == ptr->Data) { // ��� ������ ���� ��� = ������ ��� ?
			deleteptr = indexptr->Next; // ������ ��带 �����صΰ�...
			break;
		}
	}
	indexptr->Next = indexptr->Next->Next; // ������ ����� ������带 ������ ����
	indexptr->Next->Next->Prev = indexptr; // ������ ����� ��������� ���� ��带 �缳��. *����� �ʿ�
}
int main()
{
	NODE *ptr;
	int i = 0;
	Initalize();

	cout << "��� C ���� ��" << endl;
	ptr = head->Next;

	for (i = 0; i < 4; i++) {
		cout << ptr->Data;
		ptr = ptr->Next;
	}

	temp = (NODE *)malloc(sizeof(NODE));
	temp->Data = 'C';

	InsertNode(temp);

	cout << endl << "��� C ���� ��" << endl;
	ptr = head->Next;

	for (i = 0; i < 5; i++) {
		cout << ptr->Data;
		ptr = ptr->Next;
	}

	DeleteNode(temp);

	cout << endl << "��� C ���� ��" << endl;
	ptr = head->Next;

	for (i = 0; i < 4; i++) {
		cout << ptr->Data;
		ptr = ptr->Next;
	}

	_getch();

	return 0;
}

