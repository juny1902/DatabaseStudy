// Pointer3_Array2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int i = 0, sum = 0;
	for (i = 0; i <= 100; i++) {
		if ((i % 2) != 0){
			cout << i << endl;
			sum += i;
		}
	}
	cout << "sum = " << sum << endl;
	cin >> i;
    return 0;
}

