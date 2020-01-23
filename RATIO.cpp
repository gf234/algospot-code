#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

long long n, m;
// games만큼 연승했을때의 승률
long long rate(long long games) {
	return (m+games)*100/(n+games);
}
// 이분법 적용
long long solve() {
	long long lo = 0, hi = 2000000000;
	if (rate(hi) == rate(0)) return -1;
	while (lo + 1 < hi) {
		long long mid = (lo + hi) / 2;
		if (rate(mid) > rate(0))
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
		cin >> n >> m;

		long long result = solve();

		cout << result << "\n";
	}
}