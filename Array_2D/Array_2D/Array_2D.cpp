// Array_2D.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
#define STUDENT 5
#define SUBJECT 2
using namespace std;

int score[STUDENT][SUBJECT];
void DisplayTable(void)
{
	int i;
	int Total[2] = { 0,0 };
	cout << "��ȣ\t����\t����\t���" << endl;
	for (i = 0; i < STUDENT; i++) {
		cout << i << "\t" << score[i][0] << "\t" << score[i][1] << "\t" << (double)(score[i][0] + score[i][1]) / (double)SUBJECT << endl;
		Total[0] += score[i][0];
		Total[1] += score[i][1];
	}
	cout << "-------------------------------------" << endl;
	cout << "����\t" << Total[0] << "\t" << Total[1] << "\t" << endl;
	cout << "���\t" << (double)(Total[0] / STUDENT) << "\t" << (double)(Total[1] / STUDENT) << "\t" << endl;
}
int main()
{
	int n = 0;

	cout << "�л� �� ���� �Է�." << endl;
	for (n = 0; n < STUDENT; n++) {
		cout << n+1 << "�� �л��� ���� ���� = ";
		cin >> score[n][0];
		cout << n+1 << "�� �л��� ���� ���� = ";
		cin >> score[n][1];
	}
	cout << "�Է� �� !" << endl;
	DisplayTable();
	cin >> n;
	return 0;
}

