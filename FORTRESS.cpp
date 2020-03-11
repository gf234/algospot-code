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
// a에서 b까지의 거리의 제곱을 반환한다.
int sqrdist(int a, int b) {
	return sqr(y[a] - y[b]) + sqr(x[a] - x[b]);
}
// 성벽 a가 b를 포함하는지 확인한다.
bool enclose(int a, int b) {
	return r[a] > r[b] && sqrdist(a, b) < sqr(r[a] - r[b]);
}
// parent가 child의 부모노드인지 확인
bool isChild(int parent, int child) {
	if (!enclose(parent, child)) return false;
	for (int i = 0; i < n; ++i)
		// parent가 child를 직접 포함하지 않는 경우 false
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

// 트리의 최대 높이 반환
int height(TreeNode* root) {
	// 자식 서브트리의 높이의 배열
	vector<int> heights;
	for (int i = 0; i < root->children.size(); ++i)
		heights.push_back(height(root->children[i]));
	
	if (heights.empty()) return 0;
	// 디폴트 : 오름차순
	sort(heights.begin(), heights.end());
	// 자식이 2개 이상인 경우에만 잎-잎 경로를 구한다.
	if (heights.size() >= 2)
		longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
	// 제일 큰 높이 반환
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