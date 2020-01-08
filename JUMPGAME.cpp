#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int map[100][100];

int cache[100][100];

int solve(int n, int i, int j) {
	int temp = map[i][j];
	// 끝에 도달하면 성공
	if (temp == 0)
		return 1;
	// 둘 다 넘어가면 불가능
	if ((i + temp) >= n && (j + temp) >= n)
		return 0;

	// DP 이용
	int& ret = cache[i][j];
	
	if (ret != -1)
		return ret;

	if ((i + temp) < n) {
		ret = max(ret, solve(n, i + temp, j));
	}
	if ((j + temp) < n) {
		ret = max(ret, solve(n, i, j + temp));
	}

	return ret;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		int n;
		cin >> n;

		memset(cache, -1, sizeof(cache));

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> map[i][j];
			}
		}

		if (solve(n, 0, 0) == 1)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}