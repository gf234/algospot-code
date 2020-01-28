#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;

const int MAXN = 12;
const int INF = 987654321;
int n, k, m, l;
// �������� ����
int prerequisite[MAXN];
// �ش��б⿡ ������ ���� ���
int classes[10];

int cache[10][1 << MAXN];
// ��Ʈ ���� ���� �Լ�
int bitCount(int n) {
	int cnt = 0;
	while (n != 0) {
		if ((n & 1) == 1)
			cnt++;
		n >>= 1;
	}
	return cnt;
}
// semester : ���� �б�
// taken : ���ݱ��� ���� ����
int graduate(int semester, int taken) {
	// �̹� k�� �̻� ����ٸ� ����
	if (bitCount(taken) >= k) return 0;
	// �бⰡ �Ѿ�� INF ��ȯ
	if (semester == m) return INF;

	int& ret = cache[semester][taken];
	if (ret != -1) return ret;
	ret = INF;
	// �ش��б⿡�� �̹� ���������� ������ ���� ���
	int canTake = (classes[semester] & ~taken);
	// ���� ������ ���� �ʾҴٸ� canTake ��Ͽ��� ����
	for (int i = 0; i < n; ++i)
		if ((canTake & (1 << i)) && (taken & prerequisite[i]) != prerequisite[i])
			canTake &= ~(1 << i);
	// ��� �κ����� ��ȸ
	for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
		// ���б⿡ �����ϴ� ������� �Ѿ�� �κ������� �Ѿ��
		if (bitCount(take) > l) continue;
		ret = min(ret, graduate(semester + 1, taken | take) + 1);
	}
	// �ƹ��͵� ���� �ʰ� �����б�� �Ѿ��
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