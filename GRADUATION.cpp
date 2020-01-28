#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;

const int MAXN = 12;
const int INF = 987654321;
int n, k, m, l;
// 선수과목 정보
int prerequisite[MAXN];
// 해당학기에 열리는 강의 목록
int classes[10];

int cache[10][1 << MAXN];
// 비트 개수 세는 함수
int bitCount(int n) {
	int cnt = 0;
	while (n != 0) {
		if ((n & 1) == 1)
			cnt++;
		n >>= 1;
	}
	return cnt;
}
// semester : 현재 학기
// taken : 지금까지 들은 과목
int graduate(int semester, int taken) {
	// 이미 k개 이상 들었다면 종료
	if (bitCount(taken) >= k) return 0;
	// 학기가 넘어가면 INF 반환
	if (semester == m) return INF;

	int& ret = cache[semester][taken];
	if (ret != -1) return ret;
	ret = INF;
	// 해당학기에서 이미 들은과목을 제외한 과목만 고려
	int canTake = (classes[semester] & ~taken);
	// 선수 과목을 듣지 않았다면 canTake 목록에서 삭제
	for (int i = 0; i < n; ++i)
		if ((canTake & (1 << i)) && (taken & prerequisite[i]) != prerequisite[i])
			canTake &= ~(1 << i);
	// 모든 부분집합 순회
	for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
		// 한학기에 들어야하는 과목수를 넘어가는 부분집합은 넘어간다
		if (bitCount(take) > l) continue;
		ret = min(ret, graduate(semester + 1, taken | take) + 1);
	}
	// 아무것도 듣지 않고 다음학기로 넘어갈때
	ret = min(ret, graduate(semester + 1, taken));
	return ret;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> n >> k >> m >> l;
		memset(cache, -1, sizeof(cache));
		fill_n(prerequisite, MAXN, 0);
		fill_n(classes, 10, 0);

		for (int i = 0; i < n; ++i) {
			int r;
			cin >> r;
			for (int j = 0; j < r; ++j) {
				int temp;
				cin >> temp;
				prerequisite[i] |= (1 << temp);
			}
		}
		for (int i = 0; i < m; ++i) {
			int c;
			cin >> c;
			for (int j = 0; j < c; ++j) {
				int temp;
				cin >> temp;
				classes[i] |= (1 << temp);
			}
		}
		int result = graduate(0, 0);
		if (result == INF) cout << "IMPOSSIBLE\n";
		else cout << result << "\n";
	}
	return 0;
}