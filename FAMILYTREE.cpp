#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>
#include <limits>
using namespace std;

// �迭�� ���� �ּ� ������ �ذ��ϱ� ���� ���� Ʈ���� ����
struct RMQ {
	// �迭�� ����
	int n;
	// �� ������ �ּ�ġ
	vector<int> rangeMin;
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}
	// node ��尡 array[left..right] �迭�� ǥ���� ��
	// node�� ��Ʈ�� �ϴ� ����Ʈ���� �ʱ�ȭ�ϰ�, �� ������ �ּ�ġ�� ��ȯ�Ѵ�.
	int init(const vector<int>& array, int left, int right, int node) {
		if (left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}
	// node�� ǥ���ϴ� ���� array[nodeLeft..nodeRight]�� �־��� ��
	// �� ������ array[left..right]�� �������� �ּ�ġ�� ���Ѵ�.
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		// �� ������ ��ġġ ������ ���� ū���� ��ȯ : ���õ�
		if (right < nodeLeft || nodeRight < left) return 987654321;
		// node�� ǥ���ϴ� ������ array[left..right]�� ������ ���ԵǴ� ��� ����� �ּҰ��� �ٷ� ��ȯ�Ѵ�.
		if (left <= nodeLeft && nodeRight <= right)
			return rangeMin[node];
		// ���� ������ ������ Ǭ �� ����� ��ģ��.
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}
	// query()�� �ܺο��� ȣ���ϱ� ���� �������̽�
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}
	// array[index]=newValue�� �ٲ���� �� node�� ��Ʈ�� �ϴ�
	// ���� Ʈ���� �����ϰ� ��尡 ǥ���ϴ� ������ �ּ�ġ�� ��ȯ�Ѵ�.
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		if (index < nodeLeft || nodeRight < index)
			return rangeMin[node];
		if (nodeLeft == nodeRight) return rangeMin[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid), update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}
	// update()�� �ܺο��� ȣ���ϱ� ���� �������̽�
	int update(int index, int newValue) {
		return update(index, newValue, 1, 0, n - 1);
	}
};

const int MAX_N = 100000;
int n;
// Ʈ���� ��ȣ�� �Ϸù�ȣ ������ ���� ����
int no2serial[MAX_N], serial2no[MAX_N];
// locInTrip : �� ��尡 tirp�� ó�� �����ϴ� ��ġ
// depth : ����� ����
int locInTrip[MAX_N], depth[MAX_N];
int nextSerial;

// ���̰� d�� ��� here ���ϸ� ���� Ž���Ѵ�.
void traverse(int here, int d, vector<int>& trip, vector<vector<int>>& child) {
	// traverse()�� ó�� �湮���ڸ��� �Ϸ� ��ȣ�� �ο��Ѵ�.
	// -> �׻� �θ�� �ڼպ��� ���� �Ϸ� ��ȣ�� ���� �ȴ�.
	no2serial[here] = nextSerial;
	serial2no[nextSerial] = here;
	++nextSerial;
	// ���� ���
	depth[here] = d;
	// trip�� ���� ����� �Ϸù�ȣ�� �߰��Ѵ�.
	locInTrip[here] = trip.size();
	trip.push_back(no2serial[here]);
	// ��� �ڽ� ��带 �湮
	for (int i = 0; i < child[here].size(); ++i) {
		traverse(child[here][i], d + 1, trip,child);
		// �ڽ� ��带 �湮�ϰ� ���� ���� ���ƿ� ������ �ٽ� �߰��ϱ�
		trip.push_back(no2serial[here]);
	}
}
// Ʈ���� ��ȸ�ϸ� ���� �ʿ��� ������ ����ϰ�,
// RMQ ���� Ʈ���� ����� ��ȯ�Ѵ�.
RMQ* prepareRMQ(vector<vector<int>>& child) {
	nextSerial = 0;
	// ��ȸ �������� ������ ������ �Ϸ� ��ȣ�� ��´�.
	vector<int> trip;
	traverse(0, 0, trip, child);
	return new RMQ(trip);
}

// u�� v������ �Ÿ��� ����Ѵ�.
int distance(RMQ* rmq, int u, int v) {
	// trip���� ó�� ���� �ڸ��� ����Ѵ�.
	int lu = locInTrip[u], lv = locInTrip[v];
	if (lu > lv) swap(lu, lv);
	// lca : u�� v�� �ּ� ���� ����
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