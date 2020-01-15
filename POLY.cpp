#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

int n;
const int MOD = 10 * 1000 * 1000;

// n���� �簢������ �̷�����ְ�
// ù��° �ٿ� first ������ŭ �ִ� �������̳�
int cache[101][101];
int poly(int n, int first) {
	// ���� ��� : �ϳ��� ���� ���
	if (n == first) return 1;

	int& ret = cache[n][first];
	if (ret != -1) return ret;
	ret = 0;

	for (int second = 1; second <= n - first; second++) {
		int add = second + first - 1;
		add *= poly(n - first, second);
		add %= MOD;
		ret += add;
		ret %= MOD;
	}
	return ret;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		cin >> n;

		memset(cache, -1, sizeof(cache));

		// ù��° �����ϴ� ��� ��츦 ������ߵ�
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			cnt += poly(n, i);
			cnt %= MOD;
		}
		
		cout << cnt << "\n";

	}
}