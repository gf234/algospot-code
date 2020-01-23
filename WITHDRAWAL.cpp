#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
// n : �����ϴ� ������ ��
// k : ���ܵ־� �� ������ ��
// c[i] : i��° ������ ������ ��
// r[i] : i��° ���� �߰� ��� ���
int n, k;
int c[1000], r[1000];
// average ���ϰ� �� �� �ִ��� ����
// v[i] = average * c[i] - r[i]
bool decision(double average) {
	vector<double> v;
	for (int i = 0; i < n; ++i)
		v.push_back(average * c[i] - r[i]);
	sort(v.begin(), v.end());
	// ū�� k�� ����
	double sum = 0;
	for (int i = n - k; i < n; ++i)
		sum += v[i];
	return sum >= 0;
}
// �̺й� ����
double optimize() {
	double lo = -1e-9, hi = 1;
	for (int iter = 0; iter < 100; ++iter) {
		double mid = (lo + hi) / 2;
		if (decision(mid))
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
		cin >> n >> k;
		for (int i = 0; i < n; ++i) {
			cin >> r[i] >> c[i];
		}

		double result = optimize();

		printf("%.10f\n", result);

	}
}