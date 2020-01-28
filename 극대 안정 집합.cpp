#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

int n;
const int MAXN = 20;
// explodes[i] : i와 같이 두었을때 폭발하는 물질 집합의 비트마스크 표현
int explodes[MAXN];
// 주어진 집합이 안정적인지 확인
bool isStable(int set) {
	for (int i = 0; i < n; ++i)
		// 집합에 포함된 i와 같이 있을때 폭발하는 물질이 있으면 false 반환
		if ((set & (1 << i)) && (set & explodes[i]))
			return false;
	return true;
}
// 모든 극대 안정 집합의 수를 센다.
int countStableSet() {
	int ret = 0;
	// 모든 부분집합 탐색
	for (int set = 1; set < (1 << n); ++set) {
		// 안정적이지 않으면 다음으로
		if (!isStable(set)) continue;
		// 더 추가할 수 있는지 확인
		bool canExtend = false;
		for(int add = 0; add<n; ++add)
			if ((set & (1 << add)) == 0 && (explodes[add] & set) == 0) {
				canExtend = true;
				break;
			}
		if (!canExtend)
			++ret;
	}
	return ret;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{

	}
	return 0;
}