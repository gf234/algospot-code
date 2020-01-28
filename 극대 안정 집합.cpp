#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

int n;
const int MAXN = 20;
// explodes[i] : i�� ���� �ξ����� �����ϴ� ���� ������ ��Ʈ����ũ ǥ��
int explodes[MAXN];
// �־��� ������ ���������� Ȯ��
bool isStable(int set) {
	for (int i = 0; i < n; ++i)
		// ���տ� ���Ե� i�� ���� ������ �����ϴ� ������ ������ false ��ȯ
		if ((set & (1 << i)) && (set & explodes[i]))
			return false;
	return true;
}
// ��� �ش� ���� ������ ���� ����.
int countStableSet() {
	int ret = 0;
	// ��� �κ����� Ž��
	for (int set = 1; set < (1 << n); ++set) {
		// ���������� ������ ��������
		if (!isStable(set)) continue;
		// �� �߰��� �� �ִ��� Ȯ��
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