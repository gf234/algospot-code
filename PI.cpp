#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int INF = 987654321;
string N;

int classify(int a, int b) {
	string M = N.substr(a, b-a+1);

	// ��� ���� ����?
	if (M == string(M.size(), M[0])) return 1;

	// ��������?
	bool progressive = true;
	for (int i = 0; i < M.size() - 1; i++) 
		if ((M[i + 1] - M[i]) != (M[1] - M[0]))
			progressive = false;

	if (progressive && abs(M[1] - M[0]) == 1)
		return 2;

	// 2���� ���ڰ� ������ ��������?
	bool alternating = true;
	for (int i = 0; i < M.size(); i++) 
		if (M[i] != M[i % 2])
			alternating = false;

	// ������ ������ ��� ���̵� 4
	if (alternating) return 4;

	// ���������� ��� ���̵� 5
	if (progressive) return 5;

	// �̿��� ��� ���̵� 10
	return 10;
}

int cache[10002];

int memorize(int begin) {
	// ������ ���� ������ ���
	if (begin == N.size()) return 0;

	int& ret = cache[begin];
	if (ret != -1) return ret;
	ret = INF;
	// 3~5���ڷ� �ڸ���.
	for (int L = 3; L <= 5; L++) 
		// ������ ũ�⸦ �Ѿ�� �ʵ���
		if (begin + L <= N.size())
			ret = min(ret, memorize(begin + L) + classify(begin, begin + L - 1));

	return ret;
}
int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		cin >> N;

		memset(cache, -1, sizeof(cache));

		cout << memorize(0) << "\n";

	}
}