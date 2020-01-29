#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;

// 한번 살 수 있을때 가능한 방법의 수
int waysToBuy(const vector<int>& psum, int k) {
	const int MOD = 20091101;
	int ret = 0;
	// count[i] : i인 psum의 개수
	vector<long long> count(k, 0);
	for (int i = 0; i < psum.size(); ++i) 
		count[psum[i]]++;
	// 2개 이상 있는경우 2개 고르는 조합 갯수 더하기
	for (int i = 0; i < k; ++i)
		if (count[i] >= 2)
			ret = (ret + ((count[i] * (count[i] - 1)) / 2)) % MOD;
	return ret;
}
// 여러번 살 수 있을때 가능한 최대 주문의 수
int maxBuys(const vector<int>& psum, int k) {
	// ret[i] : i까지 고려했을때 최대 주문의 수
	vector<int> ret(psum.size(), 0);
	// prev[i] : psum = i가 나온 마지막 위치
	vector<int> prev(k, -1);
	// ret[i]는 주문 불가능한 경우 ret[i-1]
	// 주문 가능한 경우 마지막위치까지의 경우 + 1
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