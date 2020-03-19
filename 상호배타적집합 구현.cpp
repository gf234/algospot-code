#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>
#include <limits>
using namespace std;

// 트리를 이용한 상호배타적 집합의 구현
struct NaiveDisjointSet {
	vector<int> parent;
	NaiveDisjointSet(int n) : parent(n) {
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}
	// u가 속한 트리의 루트 번호를 반환한다.
	int find(int u) const {
		// 루트인경우 반환
		if (u == parent[u]) return u;
		// 아닌경우 재귀적으로 위로 올라감
		return find(parent[u]);
	}
	// u가 속한 트리와 v가 속한 트리를 합친다.
	void merge(int u, int v) {
		u = find(u); v = find(v);
		// 이미 같은 트리에 속한경우 리턴
		if (u == v) return;
		// 무조건 왼쪽을 오른쪽 밑으로 합치는 방법 -> 문제점 : 트리의 불균형이 올 수 있음
		parent[u] = v;
	}
};
// 랭크에 의한 합치기 최적화 방법 적용
struct OptimizedDisjointSet {
	// 랭크 : 해당 트리의 높이
	vector<int> parent, rank;
	OptimizedDisjointSet(int n) : parent(n), rank(n, 1) {
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}
	// u가 속한 트리의 루트번호를 반환한다.
	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}
	// u가 속해있는 트리와 v가 속해있는 트리를 합친다.
	void merge(int u, int v) {
		u = find(u); v = find(v);
		// 이미 같은 트리에 속해있으면 리턴
		if (u == v) return;
		// 큰쪽에 작은것을 붙이기 위해 u < v 조건 항상 만족
		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		// 랭크가 같은 경우에만 랭크를 1 높여 준다.
		if (rank[u] == rank[v]) ++rank[v];
	}
};

int main() {
}