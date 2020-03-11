#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <cstdio>
using namespace std;

// 현재 다른 점에 지배당하지 않는 점들의 목록을 저장한다.
// coords[x] = y
map<int, int> coords;

// 새로운점이 기존의 점에 지배당하는지 확인
bool isDominated(int x, int y) {
	// x보다 큰 것중 가장 왼쪽에 있는 점
	map<int, int>::iterator it = coords.lower_bound(x);
	// 그런 점이 없으면 지배 당하지 않는것
	if (it == coords.end()) return false;

	return y < it->second;
}

// 새로운 점에 의해 지배당하는 점들을 지운다
void removeDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);
	// 새로운 점보다 왼쪽에 있는 점이 없는 경우 종료
	if (it == coords.begin()) return;
	// x의 왼쪽 부터 검사
	--it;

	while (true) {
		// 지배당하지 않으면 종료
		if (it->second > y) break;

		// 이전 점이 없으면 지우고 바로 종료
		if (it == coords.begin()) {
			coords.erase(it);
			break;
		}
		// 이전 점이 있는 경우 왼쪽으로 이동하면서 반복
		else {
			map<int, int>::iterator jt = it;
			--jt;
			coords.erase(it);
			it = jt;
		}
	}
}

// 새점이 추가될때 갱신하고 지배당하지 않는 점의 개수 반환
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