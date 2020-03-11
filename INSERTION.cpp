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
	// size : �� ��带 ��Ʈ�� �ϴ� ����Ʈ���� ũ��
	int priority, size;
	Node *left, *right;

	// �ʱ�ȭ ����Ʈ ���
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

// key�� �������� 2���� Ʈ������ �и��Ѵ�.
// ( key �̸�, key �̻� )
NodePair split(Node* root, KeyType key) {
	if (root == NULL) return NodePair(NULL, NULL);
	// ��Ʈ�� key �̸��̸� ��Ʈ�� ������ ��� key �̸� -> ������ ����Ʈ���� �ɰ���.
	if (root->key < key) {
		NodePair rs = split(root->right, key);
		// ������ ����Ʈ���� key  �̸��� ���� ��Ʈ�� ������ ����Ʈ���� �����Ѵ�.
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	// ��Ʈ�� key �̻��̸� ��Ʈ�� �������� ��� key �̻� -> ���� ����Ʈ���� �ɰ���.
	NodePair ls = split(root->left, key);
	// ���� ����Ʈ���� key  �̻��� ���� ��Ʈ�� ���� ����Ʈ���� �����Ѵ�.
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}

// root : ���� Ʈ��
// node : ���� ������ ���
Node* insert(Node* root, Node* node) {
	// ������ NULL�̸� ���ο� ��尡 ��Ʈ�� ��
	if (root == NULL) return node;

	// ���ο� ����� �켱������ ������ node�� ��Ʈ�� �Ǿ�� �Ѵ�.
	if (root->priority < node->priority) {
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	// ��Ʈ�� �켱������ ������� Ű�� �������� ���� ( ��� ȣ�� )
	else if (node->key < root->key)
		root->setLeft(insert(root->left, node));
	else
		root->setRight(insert(root->right, node));
	return root;
}

// max(a) < min(b) �϶�, a�� b�� ��ģ��.
Node* merge(Node* a, Node* b) {
	if (a == NULL) return b;
	if (b == NULL) return a;
	// �켱������ �������� ��Ʈ�� �����Ѵ�.
	if (a->priority < b->priority) {
		// max(a) < min(b) �̱� ������ ...
		b->setLeft(merge(a, b->left));
		return b;
	}
	// max(a) < min(b) �̱� ������ ...
	a->setRight(merge(a->right, b));
	return a;
}

// key�� ����� ��� Ʈ���� ��Ʈ�� ��ȯ�Ѵ�.
Node* erase(Node* root, KeyType key) {
	if (root == NULL) return root;
	// root�� ����� �� ����Ʈ���� ��ģ �� ��ȯ�Ѵ�.
	if (root->key == key) {
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	// Ű�� �������� ����ʿ��� ������ �����Ѵ�.
	if (key < root->key)
		root->setLeft(erase(root->left, key));
	else
		root->setRight(erase(root->right, key));
	return root;
}

// k��° ���Ҹ� ��ȯ�Ѵ�.
Node* kth(Node* root, int k) {
	int leftSize = 0;
	if (root->left != NULL) leftSize = root->left->size;
	if (k <= leftSize) return kth(root->left, k);
	if (k == leftSize + 1) return root;
	return kth(root->right, k - leftSize - 1);
}

// key���� ���� Ű���� ���� ��ȯ�Ѵ�.
int countLessThan(Node* root, KeyType key) {
	if (root == NULL) return 0;
	// ���ʿ��� key���� ���� ���� ã�ƾ� �Ѵ�.
	if (root->key >= key)
		return countLessThan(root->left, key);
	// ls : ���� ����Ʈ���� ũ��
	int ls = (root->left ? root->left->size : 0);
	// ��Ʈ�� Ű���� ������ ��Ʈ�� ���ʼ���Ʈ���� ��� ������ ���Եȴ�.
	return ls + 1 + countLessThan(root->right, key);
}

int n, shifted[50000];
int A[50000];

void solve() {
	// 1~N������ ���ڸ� ��� �����ϴ� Ʈ���� �����.
	Node* candidates = NULL;
	for (int i = 0; i < n; ++i)
		candidates = insert(candidates, new Node(i + 1));
	
	// �ڿ������� A[]�� ä�� ������.
	for (int i = n - 1; i >= 0; --i) {
		// larger : A[]�� �� �ĺ��� �� �� ������ ū ���� ����
		int larger = shifted[i];
		// i + 1 : �ĺ����� ����
		Node* k = kth(candidates, i + 1 - larger);
		A[i] = k->key;
		// �� ���� �ĺ����� �����.
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