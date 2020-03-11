#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <cstdio>
using namespace std;

// ���� �ٸ� ���� ��������� �ʴ� ������ ����� �����Ѵ�.
// coords[x] = y
map<int, int> coords;

// ���ο����� ������ ���� ������ϴ��� Ȯ��
bool isDominated(int x, int y) {
	// x���� ū ���� ���� ���ʿ� �ִ� ��
	map<int, int>::iterator it = coords.lower_bound(x);
	// �׷� ���� ������ ���� ������ �ʴ°�
	if (it == coords.end()) return false;

	return y < it->second;
}

// ���ο� ���� ���� ������ϴ� ������ �����
void removeDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);
	// ���ο� ������ ���ʿ� �ִ� ���� ���� ��� ����
	if (it == coords.begin()) return;
	// x�� ���� ���� �˻�
	--it;

	while (true) {
		// ��������� ������ ����
		if (it->second > y) break;

		// ���� ���� ������ ����� �ٷ� ����
		if (it == coords.begin()) {
			coords.erase(it);
			break;
		}
		// ���� ���� �ִ� ��� �������� �̵��ϸ鼭 �ݺ�
		else {
			map<int, int>::iterator jt = it;
			--jt;
			coords.erase(it);
			it = jt;
		}
	}
}

// ������ �߰��ɶ� �����ϰ� ��������� �ʴ� ���� ���� ��ȯ
int registered(int x, int y) {
	if (isDominated(x, y)) return coords.size();

	removeDominated(x, y);
	coords[x] = y;
	return coords.size();
}

int main() {
	int c;
	cin >> c;
	for (int testN = 0; testN < c; ++testN) {
		int n;
		cin >> n;

		coords.clear();

		int x, y;
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			scanf_s("%d%d", &x, &y);
			cnt += registered(x, y);
		}
		cout << cnt << '\n';

	}
}