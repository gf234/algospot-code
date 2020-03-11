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

int main() {
	int c;
	cin >> c;
	for (int testN = 1; testN <= c; ++testN) {
		int n;
		cin >> n;
		int q;
		cin >> q;
		vector<int> h(n);
		vector<int> hMinus(n);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &h[i]);
			hMinus[i] = -h[i];
		}
		RMQ min(h);
		RMQ max(hMinus);
		for (int i = 0; i < q; ++i) {
			int a, b;
			scanf("%d%d", &a, &b);
			int result = -max.query(a, b) - min.query(a, b);
			printf("%d\n", result);
		}
		
	}
}