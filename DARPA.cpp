#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

int n, m;
// gap 이상이 되는 경우가 있는지 반환
bool decision(const vector<double>& location, int cameras, double gap) {
	double limit = -1;
	int installed = 0;
	for (int i = 0; i < location.size(); ++i) {
		if (limit <= location[i]) {
			++installed;
			limit = location[i] + gap;
		}
	}
	return installed >= cameras;
}
// 이분법 이용
double optimize(const vector<double>& location, int cameras) {
	double lo = 0, hi = 241;
	for (int it = 0; it < 100; ++it) {
		double mid = (lo + hi) / 2.0;
		// mid 이상이면 mid~high
		if (decision(location, cameras, mid))
			lo = mid;
		else
			// 그렇지 않으면 lo~mid
			hi = mid;
	}
	return lo;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		cin >> n >> m;
		vector<double> location;
		for (int i = 0; i < m; i++) {
			double temp;
			cin >> temp;
			location.push_back(temp);
		}
		sort(location.begin(), location.end());

		double result = optimize(location, n);
		printf("%.2f\n", result);
	}
}