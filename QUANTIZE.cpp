#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int N, S;

const int INF = 987654321;

// ������ �κ���
int A[101], pSum[101], pSqSum[101];

// ���� �����ϰ� �κ��� ���ϴ� �κ�
void precalc() {
	sort(A, A + N);
	pSum[0] = A[0];
	pSqSum[0] = A[0] * A[0];
	for (int i = 1; i < N; i++) {
		pSum[i] = pSum[i - 1] + A[i];
		pSqSum[i] = pSqSum[i - 1] + A[i] * A[i];
	}
}

// [lo, hi] �������� ������ �ּҰ� ��ȯ
int minError(int lo, int hi) {
	int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]);
	int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo - 1]);

	// �ݿø��ϱ� ���� + 0.5   ---> ����Ʈ�� �ݿø� �ȵǱ⶧��
	int m = int(0.5 + (double)sum / (hi - lo + 1));

	int ret = sqSum - 2 * m * sum + m * m * (hi - lo + 1);
	return ret;
}

// from ����, parts : ���� ����ȭ ���� ( ���ĵ� ���� �̿� )
int cache[101][11];
int quantize(int from, int parts) {
	// ������ ���������� 0 ��ȯ ( 0���� �����ϱ⶧���� N-1 ���� ����ȭ�ϰ� N�� �ҷ����� ������ ��...)
	if (from == N) return 0;
	// ���� ���ڰ� ���µ� �� ���� �� ������ INF ��ȯ 
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