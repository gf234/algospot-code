#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <cstdio>
using namespace std;

typedef int KeyType;

struct Node {
	KeyType key;
	// size : 이 노드를 루트로 하는 서브트리의 크기
	int priority, size;
	Node *left, *right;

	// 초기화 리스트 사용
	Node(const KeyType& _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) {
	}

	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }

	void calcSize() {
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};

typedef pair<Node*, Node*> NodePair;

// key를 기준으로 2개의 트립으로 분리한다.
// ( key 미만, key 이상 )
NodePair split(Node* root, KeyType key) {
	if (root == NULL) return NodePair(NULL, NULL);
	// 루트가 key 미만이면 루트의 왼쪽은 모두 key 미만 -> 오른쪽 서브트리를 쪼갠다.
	if (root->key < key) {
		NodePair rs = split(root->right, key);
		// 오른쪽 서브트리중 key  미만인 것을 루트의 오른쪽 서브트리로 설정한다.
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	// 루트가 key 이상이면 루트의 오른쪽은 모두 key 이상 -> 왼쪽 서브트리를 쪼갠다.
	NodePair ls = split(root->left, key);
	// 왼쪽 서브트리중 key  이상인 것을 루트의 왼쪽 서브트리로 설정한다.
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}

// root : 기존 트립
// node : 새로 삽입할 노드
Node* insert(Node* root, Node* node) {
	// 기존이 NULL이면 새로운 노드가 루트가 됨
	if (root == NULL) return node;

	// 새로운 노드의 우선순위가 높으면 node가 루트가 되어야 한다.
	if (root->priority < node->priority) {
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	// 루트의 우선순위가 높은경우 키를 기준으로 설정 ( 재귀 호출 )
	else if (node->key < root->key)
		root->setLeft(insert(root->left, node));
	else
		root->setRight(insert(root->right, node));
	return root;
}

// max(a) < min(b) 일때, a와 b를 합친다.
Node* merge(Node* a, Node* b) {
	if (a == NULL) return b;
	if (b == NULL) return a;
	// 우선순위를 기준으로 루트를 결정한다.
	if (a->priority < b->priority) {
		// max(a) < min(b) 이기 때문에 ...
		b->setLeft(merge(a, b->left));
		return b;
	}
	// max(a) < min(b) 이기 때문에 ...
	a->setRight(merge(a->right, b));
	return a;
}

// key를 지우고 결과 트립의 루트를 반환한다.
Node* erase(Node* root, KeyType key) {
	if (root == NULL) return root;
	// root를 지우고 양 서브트리를 합친 뒤 반환한다.
	if (root->key == key) {
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	// 키를 기준으로 어느쪽에서 지울지 결정한다.
	if (key < root->key)
		root->setLeft(erase(root->left, key));
	else
		root->setRight(erase(root->right, key));
	return root;
}

// k번째 원소를 반환한다.
Node* kth(Node* root, int k) {
	int leftSize = 0;
	if (root->left != NULL) leftSize = root->left->size;
	if (k <= leftSize) return kth(root->left, k);
	if (k == leftSize + 1) return root;
	return kth(root->right, k - leftSize - 1);
}

// key보다 작은 키값의 수를 반환한다.
int countLessThan(Node* root, KeyType key) {
	if (root == NULL) return 0;
	// 왼쪽에서 key보다 작은 값을 찾아야 한다.
	if (root->key >= key)
		return countLessThan(root->left, key);
	// ls : 왼쪽 서브트리의 크기
	int ls = (root->left ? root->left->size : 0);
	// 루트가 키보다 작으면 루트와 왼쪽서브트리는 모두 갯수에 포함된다.
	return ls + 1 + countLessThan(root->right, key);
}

int n, shifted[50000];
int A[50000];

void solve() {
	// 1~N까지의 숫자를 모두 저장하는 트립을 만든다.
	Node* candidates = NULL;
	for (int i = 0; i < n; ++i)
		candidates = insert(candidates, new Node(i + 1));
	
	// 뒤에서부터 A[]를 채워 나간다.
	for (int i = n - 1; i >= 0; --i) {
		// larger : A[]에 들어갈 후보들 중 이 수보다 큰 수의 개수
		int larger = shifted[i];
		// i + 1 : 후보들의 개수
		Node* k = kth(candidates, i + 1 - larger);
		A[i] = k->key;
		// 들어가 수는 후보에서 지운다.
		candidates = erase(candidates, k->key);
	}
}

int main() {
	int c;
	cin >> c;
	for (int testN = 1; testN <= c; ++testN) {
		cin >> n;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &shifted[i]);
		}
		
		solve();

		for (int i = 0; i < n; ++i) {
			printf("%d ", A[i]);
		}
		cout << '\n';
	}
}