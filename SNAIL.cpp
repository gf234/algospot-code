#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

int n, m;

// ³¯¾¾ => 0 : ºñ , 1 : È­Ã¢
double solve(int days, int climbed, vector<vector<double>>& cache) {
	if (days == m) return climbed >= n ? 1 : 0;

	double& ret = cache[days][climbed];
	if (ret != -1) return ret;

	ret = 0.75 * solve(days + 1, climbed + 2,cache) + 0.25 * solve(days + 1, climbed + 1,cache);
	return ret;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		cin >> n >> m;

		vector<vector<double>> cache(1000, vector<double>(1000 * 2 + 1, -1));

		printf("%.10f\n", solve(0, 0, cache));
		
	}
}