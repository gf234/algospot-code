#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

vector<int> num;
int n;

// DP 이용
int cache[500];
int solve(int start) {
	int& ret = cache[start];
	if (ret != -1)
		return ret;
	
	ret = 1;
	
	for (int next = start + 1; next < n; next++) {
		if (num[start] < num[next])
			ret = max(ret, solve(next)+1);
	}
	return ret;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		cin >> n;

		for (int i = 0; i < n; i++) {
			int temp;
			cin >> temp;
			num.push_back(temp);
		}
		int maxN = -987654321;
		// 시작 위치마다 검사
		for (int i = 0; i < n; i++) {
			memset(cache, -1, sizeof(cache));
			maxN = max(maxN, solve(i));
		}
		cout << maxN << "\n";
		num.clear();
	}
}