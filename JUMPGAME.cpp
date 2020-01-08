#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int map[100][100];

int cache[100][100];

int solve(int n, int i, int j) {
	int temp = map[i][j];
	// ���� �����ϸ� ����
	if (temp == 0)
		return 1;
	// �� �� �Ѿ�� �Ұ���
	if ((i + temp) >= n && (j + temp) >= n)
		return 0;

	// DP �̿�
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