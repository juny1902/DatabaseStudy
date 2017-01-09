#include "stdafx.h"
#include <iostream>
#define _MAX 10

using namespace std;

int main() {
	int i = 0;
	int data[_MAX];
	double sum = 0;

	while (i < _MAX) {
		cin >> data[i];
		i++;
	}
	for (i = 0; i < _MAX; i++) {
		sum += data[i];
	}
	cout << "Че = " << sum << ", ЦђБе = " << sum / _MAX << endl;
	cin >> i;
	return 0;
}