#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>
#include <limits>
using namespace std;

// Ʈ���� �̿��� ��ȣ��Ÿ�� ������ ����
struct NaiveDisjointSet {
	vector<int> parent;
	NaiveDisjointSet(int n) : parent(n) {
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}
	// u�� ���� Ʈ���� ��Ʈ ��ȣ�� ��ȯ�Ѵ�.
	int find(int u) const {
		// ��Ʈ�ΰ�� ��ȯ
		if (u == parent[u]) return u;
		// �ƴѰ�� ��������� ���� �ö�
		return find(parent[u]);
	}
	// u�� ���� Ʈ���� v�� ���� Ʈ���� ��ģ��.
	void merge(int u, int v) {
		u = find(u); v = find(v);
		// �̹� ���� Ʈ���� ���Ѱ�� ����
		if (u == v) return;
		// ������ ������ ������ ������ ��ġ�� ��� -> ������ : Ʈ���� �ұ����� �� �� ����
		parent[u] = v;
	}
};
// ��ũ�� ���� ��ġ�� ����ȭ ��� ����
struct OptimizedDisjointSet {
	// ��ũ : �ش� Ʈ���� ����
	vector<int> parent, rank;
	OptimizedDisjointSet(int n) : parent(n), rank(n, 1) {
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}
	// u�� ���� Ʈ���� ��Ʈ��ȣ�� ��ȯ�Ѵ�.
	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}
	// u�� �����ִ� Ʈ���� v�� �����ִ� Ʈ���� ��ģ��.
	void merge(int u, int v) {
		u = find(u); v = find(v);
		// �̹� ���� Ʈ���� ���������� ����
		if (u == v) return;
		// ū�ʿ� �������� ���̱� ���� u < v ���� �׻� ����
		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		// ��ũ�� ���� ��쿡�� ��ũ�� 1 ���� �ش�.
		if (rank[u] == rank[v]) ++rank[v];
	}
};

int main() {
}