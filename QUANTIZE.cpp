#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int N, S;

const int INF = 987654321;

// 수열과 부분합
int A[101], pSum[101], pSqSum[101];

// 수열 정렬하고 부분합 구하는 부분
void precalc() {
	sort(A, A + N);
	pSum[0] = A[0];
	pSqSum[0] = A[0] * A[0];
	for (int i = 1; i < N; i++) {
		pSum[i] = pSum[i - 1] + A[i];
		pSqSum[i] = pSqSum[i - 1] + A[i] * A[i];
	}
}

// [lo, hi] 구간에서 에러의 최소값 반환
int minError(int lo, int hi) {
	int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]);
	int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo - 1]);

	// 반올림하기 위해 + 0.5   ---> 디폴트는 반올림 안되기때문
	int m = int(0.5 + (double)sum / (hi - lo + 1));

	int ret = sqSum - 2 * m * sum + m * m * (hi - lo + 1);
	return ret;
}

// from 부터, parts : 남은 양자화 개수 ( 정렬된 수열 이용 )
int cache[101][11];
int quantize(int from, int parts) {
	// 끝까지 도달했으면 0 반환 ( 0부터 시작하기때문에 N-1 까지 양자화하고 N을 불렀을때 끝나는 것...)
	if (from == N) return 0;
	// 남은 숫자가 없는데 더 묶을 수 없을때 INF 반환 
	if (parts == 0) return INF;
	int& ret = cache[from][parts];
	if (ret != -1) return ret;
	ret = INF;

	for (int partSize = 1; from + partSize <= N; partSize++) 
		ret = min(ret, minError(from, from + partSize - 1) + quantize(from + partSize, parts - 1));
	
	return ret;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		cin >> N >> S;

		for (int i = 0; i < N; i++) {
			cin >> A[i];
		}
		precalc();

		memset(cache, -1, sizeof(cache));

		cout << quantize(0, S) << "\n";
	}
}