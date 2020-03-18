#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>
#include <limits>
using namespace std;

// ���� Ʈ���� ����. ������ �迭 A[]�� �κ� ����
// ������ ������ �� �ֵ��� �Ѵ�. �ʱ�ȭ�ÿ��� A[]��
// ���Ұ� ���� 0�̶�� �����Ѵ�.
struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}
	// A[0..pos]�� �κ� ���� ���Ѵ�.
	int sum(int pos) {
		// �ε����� 1���� �����Ѵٰ� ��������.
		++pos;
		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			// ���� ������ ã�� ���� ���� ��Ʈ �����
			pos &= (pos - 1);
		}
		return ret;
	}
	// A[pos]�� val�� ���Ѵ�.
	void add(int pos, int val) {
		++pos;
		while (pos < tree.size()) {
			tree[pos] += val;
			// (pos & -pos) : ������ ��Ʈ ����
			pos += (pos & -pos);
		}
	}
};

// ����Ʈ���� �̿��� Ǯ��
long long countMoves(const vector<int>& A) {
	FenwickTree tree(1000000);
	long long ret = 0;
	for (int i = 0; i < A.size(); ++i) {
		// ���ʿ��� A[i]���� ū ���� ����
		ret += tree.sum(999999) - tree.sum(A[i]);
		// A[i]�� ���� Ƚ�� + 1
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