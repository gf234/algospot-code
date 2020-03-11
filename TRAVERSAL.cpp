#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

// v[a,b) 구간으로 나누기
vector<int> slice(const vector<int>& v, int a, int b) {
	return vector<int>(v.begin() + a, v.begin() + b);
}

void printPostOrder(const vector<int>& preorder, const vector<int>& inorder) {
	// 트리에 포함된 노드의 수
	const int N = preorder.size();
	// 빈 경우 바로 종료
	if (preorder.empty()) return;
	// 루트는 전위 순회의 맨 처음 온다.
	const int root = preorder[0];
	// 중위 순회에서 루트를 찾으면 왼쪽 서브트리와 오른쪽 서브트리를 나눌 수 있다.
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