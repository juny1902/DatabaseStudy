// Array_firstD.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
#define MAX_ELEMENT 100
#define Sentinel 0
#define TRUE 1
#define FALSE 0
using namespace std;
int GetIntegerArray(int array[], int max, int sentinel);
int GetInteger(void);
void PrintIntegerArray(int array[], int n);
void ReverseIntegerArray(int array[], int n);
void SwapIntegerElements(int array[], int p1, int p2);
int GetIntegerArray(int array[], int max, int sentinel) // �迭�� �ִ밪�� �Է¹޾� �� ���ҿ� ���� �����ϰ� �迭�� ũ�⸦ ��ȯ.
{
	int n, value;
	n = 0;
	while (TRUE) {
		cout << "==>" ;
		value = GetInteger(); // �������� �Է¹���.
		if (value == sentinel) break; // ������ = ��Ƽ�� �̸� Ż��.
		if (n == max) cout << "�� ���� �ʰ���." << endl; // �迭�� ���� ī���Ϳ� ��ǥ �迭 ũ�Ⱑ ������ ?
		array[n] = value; // �迭�� �� ���ҿ� ������ ����
		n++;
	}
	return n; // n (�迭�� ũ��) ��ȯ
}
int GetInteger(void) 
{
	int n;
	cin >> n; // n �Է¹޾Ƽ� ��ȯ.
	return n;
}
void PrintIntegerArray(int array[], int n) // n ũ���� array �Է¹޾Ƽ�
{
	int i;
	for (i = 0; i < n; i++)
	{
		cout << array[i] << endl; // array[0]~[n] ���� ����� 
	}
}
void ReverseIntegerArray(int array[], int n)
{
	int i;
	for (i = 0; i < n / 2; i++) // �迭�� ũ���� ���� (�߰� ���ұ���)
	{
		SwapIntegerElements(array, i, n - i - 1); // �迭(array), ���� ����, ��Ī�Ǵ� ���� (�ִ�ũ�� - ���� ���� - 1) 
	}
}
void SwapIntegerElements(int array[], int p1, int p2) // array ���� p1 �� p2 �� ��ȯ��.
{
	int tmp;
	tmp = array[p1]; // p1 �ӽ�����.
	
	array[p1] = array[p2]; // p2�� ���� p1�� ���� ����.
	array[p2] = tmp; // �ӽ������ p1 ���� p2�� ���� ����.
}
int main()
{
	int list[MAX_ELEMENT], n;

	cout << "������ �������� �Է��ϼ���." << endl << "0�� �Է��ϸ� �Է� ����" << endl;
	n = GetIntegerArray(list, MAX_ELEMENT, Sentinel); // �迭 �Է¹ޱ�
	ReverseIntegerArray(list, n); // �迭 ������
	PrintIntegerArray(list, n); // �迭 ���
	cin >> n;
    return 0;
}

