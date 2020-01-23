#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
// monthlyPayment ��ŭ �������� ���� ������� ��
double balance(double amount, int duration, double rates, double monthlyPayment) {
	double balance = amount;
	for (int i = 0; i < duration; ++i) {
		balance *= (1.0 + (rates / 12.0) / 100.0);

		balance -= monthlyPayment;
	}
	return balance;
}

double payment(double amount, int duration, double rates) {
	// lo : �ƿ� �Ȱ��� ���
	// hi : �ѹ��� �� ���� ���
	double lo = 0, hi = amount * (1.0 + (rates / 12.0) / 100.0);
	for (int iter = 0; iter < 100; ++iter) {
		double mid = (lo + hi) / 2.0;
		if (balance(amount, duration, rates, mid) <= 0)
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		double n, p;
		int m;
		cin >> n >> m >> p;

		double result = payment(n, m, p);

		printf("%.10f\n", result);
	}
}