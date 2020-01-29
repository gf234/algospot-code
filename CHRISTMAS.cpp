#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;

// �ѹ� �� �� ������ ������ ����� ��
int waysToBuy(const vector<int>& psum, int k) {
	const int MOD = 20091101;
	int ret = 0;
	// count[i] : i�� psum�� ����
	vector<long long> count(k, 0);
	for (int i = 0; i < psum.size(); ++i) 
		count[psum[i]]++;
	// 2�� �̻� �ִ°�� 2�� ���� ���� ���� ���ϱ�
	for (int i = 0; i < k; ++i)
		if (count[i] >= 2)
			ret = (ret + ((count[i] * (count[i] - 1)) / 2)) % MOD;
	return ret;
}
// ������ �� �� ������ ������ �ִ� �ֹ��� ��
int maxBuys(const vector<int>& psum, int k) {
	// ret[i] : i���� ��������� �ִ� �ֹ��� ��
	vector<int> ret(psum.size(), 0);
	// prev[i] : psum = i�� ���� ������ ��ġ
	vector<int> prev(k, -1);
	// ret[i]�� �ֹ� �Ұ����� ��� ret[i-1]
	// �ֹ� ������ ��� ��������ġ������ ��� + 1
	for (int i = 0; i < psum.size(); ++i) {
		if (i > 0)
			ret[i] = ret[i - 1];
		else
			ret[i] = 0;
		int loc = prev[psum[i]];
		if (loc != -1) ret[i] = max(ret[i], ret[loc] + 1);
		prev[psum[i]] = i;
	}
	return ret.back();
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int n, k;
		cin >> n >> k;
		vector<int> d(n);
		vector<int> psum(n+1);
		for (int i = 0; i < n; ++i) {
			int temp;
			scanf("%d", &temp);
			d[i] = temp;
		}
		psum[0] = 0;
		for (int i = 1; i <= n; ++i) {
			psum[i] = (psum[i - 1] + d[i-1])%k;
		}
		printf("%d %d\n", waysToBuy(psum, k), maxBuys(psum, k));
	}
	return 0;
}