#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

// v[a,b) �������� ������
vector<int> slice(const vector<int>& v, int a, int b) {
	return vector<int>(v.begin() + a, v.begin() + b);
}

void printPostOrder(const vector<int>& preorder, const vector<int>& inorder) {
	// Ʈ���� ���Ե� ����� ��
	const int N = preorder.size();
	// �� ��� �ٷ� ����
	if (preorder.empty()) return;
	// ��Ʈ�� ���� ��ȸ�� �� ó�� �´�.
	const int root = preorder[0];
	// ���� ��ȸ���� ��Ʈ�� ã���� ���� ����Ʈ���� ������ ����Ʈ���� ���� �� �ִ�.
	const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();

	const int R = N - 1 - L;

	printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
	printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));

	cout << root << ' ';
}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; ++i) {
		int n;
		cin >> n;

		vector<int> preorder(n);
		vector<int> inorder(n);

		for (int i = 0; i < n; ++i) {
			cin >> preorder[i];
		}
		for (int i = 0; i < n; ++i) {
			cin >> inorder[i];
		}
		printPostOrder(preorder, inorder);
		cout << '\n';
	}
}