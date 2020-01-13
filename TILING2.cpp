#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int N;

// ������ ���� 1ĭ���� ä���� 2ĭ���� ä������ ����
int cache[101];
int solve(int n) {
	if (n == 1) return 1;
	if (n == 2) return 2;

	int& ret = cache[n];
	if (ret != -1) return ret;
	
	ret = (solve(n - 1) % 1000000007) + (solve(n - 2) % 1000000007);
	
	return ret % 1000000007;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		cin >> N;

		memset(cache, -1, sizeof(cache));

		cout << solve(N) << "\n";
	}
}