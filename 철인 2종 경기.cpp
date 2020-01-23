#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

double t;
vector<double> runSpeed, cycleSpeed;
// run�϶� i��°�� �ð�
double time(int i, double run) {
	double cycle = t - run;
	return run / runSpeed[i] + cycle / cycleSpeed[i];
}
// others - cheater�� ��ȯ
double diff(double r) {
	int n = runSpeed.size();
	double cheater = time(n - 1, r);
	double others = time(0, r);
	for (int i = 1; i < n - 1; ++i)
		others = min(others, time(i, r));
	return others - cheater;
}
// ��а˻����� �ִ밪 ã��
double maxDifference() {
	double lo = 0, hi = t;
	for (int it = 0; it < 100; ++it) {
		double aab = (2 * lo + hi) / 3;
		double abb = (lo + 2 * hi) / 3;
		if (diff(aab) > diff(abb))
			hi = abb;
		else
			lo = aab;
	}
	return (lo + hi) / 2;
}

int main() {
	// ������ �� (eof)�� ������ ����
	while (cin >> t) {
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i) {
			double a, b;
			cin >> a >> b;
			runSpeed.push_back(a);
			cycleSpeed.push_back(b);
		}

		double maxRun = maxDifference();
		double maxDiff = diff(maxRun);
		if (maxDiff >= 0)
			printf("The cheater can win by %.0f seconds with r = %.2fkm and k = %.2fkm.\n", diff(maxRun) * 3600, maxRun, t - maxRun);
		else
			printf("The cheater cannot win.\n");
	}
	
}