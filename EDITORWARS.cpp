#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstring>
#include <cstdio>
#include <limits>
using namespace std;

struct BipartiteUnionFind {
	// parent[i] = i�� �θ� ���, ��Ʈ�̸� �ڽ�
	// rank[i] = i�� ��Ʈ�� ���, i�� ��Ʈ���ϴ� Ʈ���� ��ũ
	// enemy[i] = i�� ��Ʈ�� ���, �ش� ���հ� ���� ������ ������ ��Ʈ�� ��ȣ ( ���� ��� -1 )
	// size[i] = i�� ��Ʈ�� ���, �ش� ������ ũ��
	vector<int> parent, rank, enemy, size;
	BipartiteUnionFind(int n) : parent(n), rank(n, 0), enemy(n, -1), size(n, 1) {
		for (int i = 0; i < n; ++i) parent[i] = i;
	}
	// u�� �����ִ� Ʈ���� ��Ʈ�� ��ȯ�Ѵ�.
	int find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}
	// u�� v�� ��ģ��. ( ��ũ�� �̿��� ū �ʿ� �������� ���δ�. )
	int merge(int u, int v) {
		// u�� v�� �������� ��� ������ �ϳ��� ��ȯ�Ѵ�..
		if (u == -1 || v == -1) return max(u, v);
		u = find(u); v = find(v);
		// �̹� ���� ���� Ʈ���� ���� ���
		if (u == v) return u;
		if (rank[u] > rank[v]) swap(u, v);
		// �׻� u < v --> v�� u�� ���δ�.
		if (rank[u] == rank[v]) rank[v]++;
		parent[u] = v;
		size[v] += size[u];
		return v;
	}
	// u�� v�� ���� ���̴�. ����� �Ͼ�ٸ� false, �ƴϸ� true�� ��ȯ�Ѵ�.
	bool dis(int u, int v) {
		u = find(u); v = find(v);
		// ���� ���տ� ���ϸ� ���
		if (u == v) return false;
		// ���� ���� ���� ����
		int a = merge(u, enemy[v]), b = merge(v, enemy[u]);
		enemy[a] = b; enemy[b] = a;
		return true;
	}
	// u�� v�� ���� ������. ����� �Ͼ�ٸ� false, �ƴϸ� true�� ��ȯ�Ѵ�.
	bool ack(int u, int v) {
		u = find(u); v = find(v);
		// ���� ��������̸� ���
		if (enemy[u] == v) return false;
		// ������ ���� ��
		int a = merge(u, v), b = merge(enemy[u], enemy[v]);
		enemy[a] = b;
		// *** �� ���մ� �����ϴ� ������ ������ b = -1 �ϼ��� �ִ�. ***
		if (b != -1) enemy[b] = a;
		return true;
	}
};

int n;

// �� ��Ƽ�� �� ���ɼ��� �ִ� �ִ� �ο��� ���Ѵ�.
int maxParty(const BipartiteUnionFind& buf) {
	int ret = 0;
	for(int node = 0; node <n;++node)
		// ��Ʈ�� ���
		if (buf.parent[node] == node) {
			int enemy = buf.enemy[node];
			// ���� ���� ���� �ι� ���� �ʱ� ����, enemy < node�� ��츸 ����.
			// enemy == -1�� ��쵵 ��Ȯ�� �� ���� ���� �ȴ�.
			if (enemy > node) continue;
			int mySize = buf.size[node];
			int enemySize = (enemy == -1 ? 0 : buf.size[enemy]);
			// �� ���� �� ū ������ ���Ѵ�.
			ret += max(mySize, enemySize);
		}
	return ret;
}

int main() {
	int c;
	cin >> c;
	for (int tn = 1; tn <= c; ++tn) {
		int m;
		cin >> n >> m;

		char comments[4];
		int a, b;
		BipartiteUnionFind uf(n);
		// ����� �Ͼ���� Ȯ���Ѵ�.
		bool is_contradiction = false;
		int pos;
		// ***** ���ܰ� �߻��ص� �Է��� ��� �޾ƾ���!!! *****
		for (int i = 1; i <= m; ++i) {
			scanf("%s%d%d", comments , &a, &b);
			// strcmp : ���ڿ��� ������ 0 ��ȯ
			if (!is_contradiction) {
				if (strcmp(comments, "ACK") == 0) {
					if (!uf.ack(a, b)) {
						is_contradiction = true;
						pos = i;
					}
				}
				else {
					if (!uf.dis(a, b)) {
						is_contradiction = true;
						pos = i;
					}
				}
			}
		}
		if(!is_contradiction)
			cout << "MAX PARTY SIZE IS " << maxParty(uf) << '\n';
		else
			cout << "CONTRADICTION AT " << pos << '\n';
	}
}