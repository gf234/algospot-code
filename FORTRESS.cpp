#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

int n;
int x[100], y[100], r[100];

struct TreeNode {
	vector<TreeNode*> children;
};

int sqr(int x) {
	return x * x;
}
// a���� b������ �Ÿ��� ������ ��ȯ�Ѵ�.
int sqrdist(int a, int b) {
	return sqr(y[a] - y[b]) + sqr(x[a] - x[b]);
}
// ���� a�� b�� �����ϴ��� Ȯ���Ѵ�.
bool enclose(int a, int b) {
	return r[a] > r[b] && sqrdist(a, b) < sqr(r[a] - r[b]);
}
// parent�� child�� �θ������� Ȯ��
bool isChild(int parent, int child) {
	if (!enclose(parent, child)) return false;
	for (int i = 0; i < n; ++i)
		// parent�� child�� ���� �������� �ʴ� ��� false
		if (i != parent && i != child && enclose(i, child) && enclose(parent, i))
			return false;
	return true;
}

TreeNode* getTree(int root) {
	TreeNode* ret = new TreeNode();
	for (int ch = 0; ch < n; ++ch) {
		if (isChild(root, ch))
			ret->children.push_back(getTree(ch));
	}
	return ret;
}

int longest;

// Ʈ���� �ִ� ���� ��ȯ
int height(TreeNode* root) {
	// �ڽ� ����Ʈ���� ������ �迭
	vector<int> heights;
	for (int i = 0; i < root->children.size(); ++i)
		heights.push_back(height(root->children[i]));
	
	if (heights.empty()) return 0;
	// ����Ʈ : ��������
	sort(heights.begin(), heights.end());
	// �ڽ��� 2�� �̻��� ��쿡�� ��-�� ��θ� ���Ѵ�.
	if (heights.size() >= 2)
		longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
	// ���� ū ���� ��ȯ
	return heights.back() + 1;
}

int solve(TreeNode* root) {
	longest = 0;

	int h = height(root);
	return max(longest, h);
}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; ++i) {
		cin >> n;

		for (int j = 0; j < n; ++j) {
			cin >> x[j] >> y[j] >> r[j];
		}

		TreeNode* root = getTree(0);
		int result = solve(root);

		cout << result << '\n';
	}
}