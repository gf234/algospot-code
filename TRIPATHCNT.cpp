#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int n;
int tri[101][101];

// i, j에서 최대값을 찾는 함수
int pathCache[101][101];
int path(int i, int j) {
	if (i == n - 1) return tri[i][j];

	int& ret = pathCache[i][j];
	if (ret != -1) return ret;
	
	ret = tri[i][j] + max(path(i+1,j), path(i+1,j+1));
	return ret;
}

// i, j에서 최대 경로의 개수를 구하는 함수
int cache[101][101];
int pathCnt(int i, int j) {
	if (i == n - 1) return 1;

	int& ret = cache[i][j];
	if (ret != -1) return ret;
	ret = 0;

	if (path(i + 1, j) >= path(i + 1, j + 1)) ret += pathCnt(i + 1, j);
	if (path(i + 1, j) <= path(i + 1, j + 1)) ret += pathCnt(i + 1, j+1);

	return ret;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		cin >> n;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i + 1; j++) {
				cin >> tri[i][j];
			}
		}
		
		memset(pathCache, -1, sizeof(pathCache));
		path(0, 0);

		memset(cache, -1, sizeof(cache));
		cout << pathCnt(0, 0) << "\n";
	}
}