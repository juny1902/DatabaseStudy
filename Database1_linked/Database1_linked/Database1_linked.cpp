/*

	���� ��ũ�� ����Ʈ

	1.���(����)�� ��ũ(��罽)�� ������ -->  ��-��-��-��-��
	2.����� �� �տ��� �����, ������ ���ϳ�尡 ��ġ. �����͸� �������� ����. --> (���) - A - B - C - D - (����)
	3.��ũ�� ����Ʈ�� �⺻ ���� : (���) -> A -> B -> C -> D -> (����)
	�� ���� ��ũ�� ����Ʈ : �ڽ��� ��忡�� ���� ��常�� ����ų �� �ִ� ����.

	�迭���� ������
	1.�迭 = ���ӵ� �޸� ���. ���Ľ� ������
	2.����Ʈ = �ݵ�� ���������� ����
	2.���������� ���� �����͸� ���� �����ϴ� ����

	�ֿ� �˰���
	1.��� ���� ex) (���) -> A -> B -> �� -> D -> E -> (����)
		�� 1. ���ο� ��� ����
		�� 2. ���ο� ��尡 ���Ե� ��ġ�� �˻�
		�� 3. ���ο� ��尡 ���Ե� ��ġ�� ���� ���� ����(C -> D)
		�� 4. ���Ե� ��ġ�� ���� ��带 ���ο� ��忡 ����(B -> C)
	2.��� ����
		�� 1. ���� ���� ������ ��带 ����ų ������ ����
		�� 2. ������ ��� �˻�
		�� 3. ���� ��尡 ������ ��带 �ǳ� �ٰ� ���� ��带 ����Ű���� ��ũ ����.
		�� 4. ������ ����� �޸� �Ҵ� ����

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
	cout << "������ ���� �˰��� (�迭 �̿�)" << endl;
	int i, temp1, temp2;
	c = 'C';

	for (i = 0; i < 5; i++) {
		cout << Data[i] << "\t";
	}

	for (i = 0; i < 5; i++) {
		if (Data[i] > c) break; // Data[i]�� c���� ū ���� �������� i���� ��.
	}
	temp1 = Data[i]; // Data[i] �� ���� �ӽ�����.
	Data[i] = c; // Data[i] �� c�� ���� ����.
	i++;

	for (; i < 5; i++) {
		temp2 = Data[i];
		Data[i] = temp1; // �迭�� ����, �ӽð��� �̿��Ͽ� ���� ���� �о���� ��. 100
		temp1 = temp2;
	}

	cout << endl << "���� �Ϸ�" << endl;
	for (i = 0; i < 5; i++) {
		cout << Data[i] << "\t";
	}
	_getch();
	return 0;
}
#endif // ARRAY_VER
#if NODE_VER
typedef struct _NODE {
	char Data; // ����� ���� ����Ǵ� ��
	struct _NODE *Next; // ��尡 ����Ű�� ��.
} NODE;

NODE *head, *tail, *temp;
NODE *temp1, *temp2, *temp3, *temp4;

void Initialize(void);
void InsertNode(NODE *);
void DeleteNode(NODE *);
void Initialize(void)
{
	NODE *ptr;
	head = (NODE *)malloc(sizeof(NODE)); // NODE�� ũ�⸸ŭ �޸� ���� �Ҵ�.
	tail = (NODE *)malloc(sizeof(NODE));

	temp1 = (NODE *)malloc(sizeof(NODE));
	temp1->Data = 'A'; // temp1 ����ü ������ Data �׸��� ���� 'A'
	head->Next = temp1; // ����� ���� ���� 'A' (temp1)
	temp1->Next = tail; // 'A' (temp1)�� ���� ���� '��'
	tail->Next = tail; // ���� ���� ���� '��'
	ptr = temp1; // ���� �����ʹ� temp1

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
	for (indexptr = head; indexptr != tail; indexptr = indexptr->Next) { // �ε����� ������ ���ϱ��� ��� �ϳ��� �ǳʶٸ� ����
		if (indexptr->Next->Data > ptr->Data) break; // ��� ����� ���� �����Ͱ� ���� �����ͺ��� ũ�� Ż�� (�ε��� ������ ���� ����ä��)
	}

	ptr->Next = indexptr->Next; // ������ ���(ptr) �� ���� ��带 ���Ե� ��ġ(indexptr) �� ���� ��忡 ����
	indexptr->Next = ptr; // ������ ����� ���� ��带 ������ ���� ����
}
void DeleteNode(NODE *ptr)
{
	NODE *indexptr; // ���� ��带 ����ų ������
	NODE *deleteptr=0; // ������ ��带 ����ų ������
	for (indexptr = head; indexptr != tail; indexptr = indexptr->Next) {
		if (indexptr->Next->Data == ptr->Data) {
			deleteptr = indexptr->Next; // ������ ���� �ε��� �������� ���� ��� 
			break;
		}
	}
	indexptr->Next = indexptr->Next->Next; // ������ �������� ���� ��带 ������ �������� ���� ���� ����
	

}
void main()
{
	NODE *ptr;
	int i = 0;
	Initialize();
	ptr = head->Next; // �������� ��ġ�� ù��° ��� (��� ����)
	cout << "���� �� : ";
	for (i = 0; i < 4; i++) {
		cout << ptr->Data; // ����� �����͸� ���
		ptr = ptr->Next; // ���� ���� �̵�.
	}

	temp = (NODE *)malloc(sizeof(NODE));
	temp->Data = 'C';
	InsertNode(temp);

	ptr = head->Next; // �������� ��ġ�� ù��° ��� (��� ����)
	cout << endl << "���� �� : ";
	for (i = 0; i < 5; i++) {
		cout << ptr->Data; // ����� �����͸� ���
		ptr = ptr->Next; // ���� ���� �̵�.
	}

	DeleteNode(temp);
	ptr = head->Next; // �������� ��ġ�� ù��° ��� (��� ����)
	cout << endl << "���� �� : ";
	for (i = 0; i < 5; i++) {
		cout << ptr->Data; // ����� �����͸� ���
		ptr = ptr->Next; // ���� ���� �̵�.
	}
	_getch();

}


#endif // NODE_VER
