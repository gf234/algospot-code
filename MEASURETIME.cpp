#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>
#include <limits>
using namespace std;

// 펜윅 트리의 구현. 가상의 배열 A[]의 부분 합을
// 빠르게 구현할 수 있도록 한다. 초기화시에는 A[]의
// 원소가 전부 0이라고 생각한다.
struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}
	// A[0..pos]의 부분 합을 구한다.
	int sum(int pos) {
		// 인덱스가 1부터 시작한다고 생각하자.
		++pos;
		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			// 다음 구간을 찾기 위해 최종 비트 지우기
			pos &= (pos - 1);
		}
		return ret;
	}
	// A[pos]에 val을 더한다.
	void add(int pos, int val) {
		++pos;
		while (pos < tree.size()) {
			tree[pos] += val;
			// (pos & -pos) : 마지막 비트 추출
			pos += (pos & -pos);
		}
	}
};

// 팬윅트리를 이용한 풀이
long long countMoves(const vector<int>& A) {
	FenwickTree tree(1000000);
	long long ret = 0;
	for (int i = 0; i < A.size(); ++i) {
		// 왼쪽에서 A[i]보다 큰 수의 개수
		ret += tree.sum(999999) - tree.sum(A[i]);
		// A[i]의 등장 횟수 + 1
		tree.add(A[i], 1);
	}
	return ret;
}

int main() {
	int c;
	cin >> c;
	for (int testN = 1; testN <= c; ++testN) {
		int n;
		cin >> n;
		
		vector<int> A(n);

		for (int i = 0; i < n; ++i) {
			scanf("%d", &A[i]);
		}
		long long result = countMoves(A);
		cout << result << '\n';
	}
}