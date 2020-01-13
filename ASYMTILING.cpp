#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

int n;
const int MOD = 1000000007;

// ��ü ����� �� ���ϱ�
int cache[101];
int tiling(int pos) {
	if (pos <= 1) return 1;
	
	int& ret = cache[pos];
	if (ret != -1) return ret;

	ret = (tiling(pos - 1) + tiling(pos - 2)) % MOD;
	return ret;
}

// ��ü ����� �� �߿��� ��Ī�ΰ� ����
int asymmetric(int width) {
	if (width % 2 == 1)
		return (tiling(width) - tiling(width / 2) + MOD) % MOD;
	
	return (tiling(width) + MOD - (tiling(width / 2) + tiling(width / 2 - 1)) % MOD) % MOD;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		cin >> n;

		memset(cache, -1, sizeof(cache));

		cout << asymmetric(n) << "\n";
	}
}