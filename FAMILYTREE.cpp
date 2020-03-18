#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>
#include <limits>
using namespace std;

// 배열의 구간 최서 쿼리를 해결하기 위한 구간 트리의 구현
struct RMQ {
	// 배열의 길이
	int n;
	// 각 구간의 최소치
	vector<int> rangeMin;
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}
	// node 노드가 array[left..right] 배열을 표현할 때
	// node를 루트로 하는 서브트리를 초기화하고, 이 구간의 최소치를 반환한다.
	int init(const vector<int>& array, int left, int right, int node) {
		if (left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}
	// node가 표현하는 범위 array[nodeLeft..nodeRight]가 주어질 때
	// 이 범위와 array[left..right]의 교집합의 최소치를 구한다.
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		// 두 구간이 겹치치 않으면 아주 큰값을 반환 : 무시됨
		if (right < nodeLeft || nodeRight < left) return 987654321;
		// node가 표현하는 범위가 array[left..right]에 완전히 포함되는 경우 저장된 최소값을 바로 반환한다.
		if (left <= nodeLeft && nodeRight <= right)
			return rangeMin[node];
		// 양쪽 구간을 나눠서 푼 뒤 결과를 합친다.
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}
	// query()를 외부에서 호출하기 위한 인터페이스
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}
	// array[index]=newValue로 바뀌었을 때 node를 루트로 하는
	// 구간 트리를 갱신하고 노드가 표현하는 구간의 최소치를 반환한다.
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		if (index < nodeLeft || nodeRight < index)
			return rangeMin[node];
		if (nodeLeft == nodeRight) return rangeMin[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid), update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}
	// update()를 외부에서 호출하기 위한 인터페이스
	int update(int index, int newValue) {
		return update(index, newValue, 1, 0, n - 1);
	}
};

const int MAX_N = 100000;
int n;
// 트리의 번호와 일련번호 사이의 대응 관계
int no2serial[MAX_N], serial2no[MAX_N];
// locInTrip : 각 노드가 tirp에 처음 등장하는 위치
// depth : 노드의 깊이
int locInTrip[MAX_N], depth[MAX_N];
int nextSerial;

// 깊이가 d인 노드 here 이하를 전위 탐색한다.
void traverse(int here, int d, vector<int>& trip, vector<vector<int>>& child) {
	// traverse()가 처음 방문하자마자 일련 번호를 부여한다.
	// -> 항상 부모는 자손보다 작은 일련 번호를 갖게 된다.
	no2serial[here] = nextSerial;
	serial2no[nextSerial] = here;
	++nextSerial;
	// 깊이 계산
	depth[here] = d;
	// trip에 현재 노드의 일련번호를 추가한다.
	locInTrip[here] = trip.size();
	trip.push_back(no2serial[here]);
	// 모든 자식 노드를 방문
	for (int i = 0; i < child[here].size(); ++i) {
		traverse(child[here][i], d + 1, trip,child);
		// 자식 노드를 방문하고 현재 노드로 돌아올 때마다 다시 추가하기
		trip.push_back(no2serial[here]);
	}
}
// 트리를 순회하며 각종 필요한 정보를 계산하고,
// RMQ 구간 트리를 만들어 반환한다.
RMQ* prepareRMQ(vector<vector<int>>& child) {
	nextSerial = 0;
	// 순회 과정에서 만나는 노드들의 일련 번호를 담는다.
	vector<int> trip;
	traverse(0, 0, trip, child);
	return new RMQ(trip);
}

// u와 v사이의 거리를 계산한다.
int distance(RMQ* rmq, int u, int v) {
	// trip에서 처음 나온 자리를 계산한다.
	int lu = locInTrip[u], lv = locInTrip[v];
	if (lu > lv) swap(lu, lv);
	// lca : u와 v의 최소 공통 조상
	int lca = serial2no[rmq->query(lu, lv)];
	return depth[u] + depth[v] - 2 * depth[lca];
}

int main() {
	int c;
	scanf("%d", &c);
	for (int testN = 1; testN <= c; ++testN) {
		scanf("%d", &n);
		int q;
		scanf("%d", &q);
		vector<vector<int>> child(n);
		for (int i = 1; i < n; ++i) {
			int temp;
			scanf("%d", &temp);
			child[temp].push_back(i);
		}
		RMQ* rmq = prepareRMQ(child);

		for (int i = 0; i < q; ++i) {
			int a, b;
			scanf("%d%d", &a, &b);
			int result = distance(rmq, a, b);
			printf("%d\n", result);
		}
		delete rmq;
	}
}