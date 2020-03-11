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