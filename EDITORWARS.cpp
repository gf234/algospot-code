#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstring>
#include <cstdio>
#include <limits>
using namespace std;

struct BipartiteUnionFind {
	// parent[i] = i의 부모 노드, 루트이면 자신
	// rank[i] = i가 루트인 경우, i를 루트로하는 트리의 랭크
	// enemy[i] = i가 루트인 경우, 해당 집합과 적대 관계인 집합의 루트의 번호 ( 없는 경우 -1 )
	// size[i] = i가 루트인 경우, 해당 집합의 크기
	vector<int> parent, rank, enemy, size;
	BipartiteUnionFind(int n) : parent(n), rank(n, 0), enemy(n, -1), size(n, 1) {
		for (int i = 0; i < n; ++i) parent[i] = i;
	}
	// u가 속해있는 트리의 루트를 반환한다.
	int find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}
	// u와 v를 합친다. ( 랭크를 이용해 큰 쪽에 작은것을 붙인다. )
	int merge(int u, int v) {
		// u나 v가 공집합인 경우 나머지 하나를 반환한다..
		if (u == -1 || v == -1) return max(u, v);
		u = find(u); v = find(v);
		// 이미 둘이 같은 트리에 속한 경우
		if (u == v) return u;
		if (rank[u] > rank[v]) swap(u, v);
		// 항상 u < v --> v에 u를 붙인다.
		if (rank[u] == rank[v]) rank[v]++;
		parent[u] = v;
		size[v] += size[u];
		return v;
	}
	// u와 v가 서로 적이다. 모순이 일어났다면 false, 아니면 true를 반환한다.
	bool dis(int u, int v) {
		u = find(u); v = find(v);
		// 같은 집합에 속하면 모순
		if (u == v) return false;
		// 적의 적은 나의 동지
		int a = merge(u, enemy[v]), b = merge(v, enemy[u]);
		enemy[a] = b; enemy[b] = a;
		return true;
	}
	// u와 v가 서로 동지다. 모순이 일어났다면 false, 아니면 true를 반환한다.
	bool ack(int u, int v) {
		u = find(u); v = find(v);
		// 서로 적대관계이면 모순
		if (enemy[u] == v) return false;
		// 동지의 적은 적
		int a = merge(u, v), b = merge(enemy[u], enemy[v]);
		enemy[a] = b;
		// *** 두 집합다 적대하는 집합이 없으면 b = -1 일수도 있다. ***
		if (b != -1) enemy[b] = a;
		return true;
	}
};

int n;

// 한 파티에 올 가능성이 있는 최대 인원을 구한다.
int maxParty(const BipartiteUnionFind& buf) {
	int ret = 0;
	for(int node = 0; node <n;++node)
		// 루트인 경우
		if (buf.parent[node] == node) {
			int enemy = buf.enemy[node];
			// 같은 모임 쌍을 두번 세지 않기 위해, enemy < node인 경우만 센다.
			// enemy == -1인 경우도 정확히 한 번씩 세개 된다.
			if (enemy > node) continue;
			int mySize = buf.size[node];
			int enemySize = (enemy == -1 ? 0 : buf.size[enemy]);
			// 두 집합 중 큰 집합을 더한다.
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
		// 모순이 일어났는지 확인한다.
		bool is_contradiction = false;
		int pos;
		// ***** 예외가 발생해도 입력을 모두 받아야함!!! *****
		for (int i = 1; i <= m; ++i) {
			scanf("%s%d%d", comments , &a, &b);
			// strcmp : 문자열이 같으면 0 반환
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