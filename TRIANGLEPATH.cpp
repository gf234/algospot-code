#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int n;
int tri[100][100];

// DP ÀÌ¿כ
int cache[100][100];
int path(int i, int j) {
	if (i == n - 1)
		return tri[i][j];

	int& ret = cache[i][j];
	if (ret != -1)
		return ret;

	return ret = max(path(i + 1, j), path(i + 1, j + 1)) + tri[i][j];
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		cin >> n;

		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < i; j++) {
				cin >> tri[i - 1][j];
			}
		}
		memset(cache, -1, sizeof(cache));

		cout << path(0,0) << "\n";
	}
}