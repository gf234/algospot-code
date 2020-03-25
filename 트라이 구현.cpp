#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <string>
using namespace std;

const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; }

// Ʈ������ ��� ����ü
struct TrieNode {
	TrieNode* children[ALPHABETS];
	// �� ��忡�� �����ϴ� ���ڿ��� ��ȣ. ������ -1
	int terminal;
	// �� ��带 ��Ʈ�� �ϴ� Ʈ���̿� ���� ���� �߰��� �ܾ��� ��ȣ. -1�� �ʱ�ȭ
	int first;
	// �� ��带 ��Ʈ���ϴ� Ʈ���̿� ��ȣ id�� ���ڿ� key�� �߰��Ѵ�.
	void insert(const char* key, int id) {
		// first�� �켱 ����
		if (first == -1) first = id;
		// ���ڿ��� ������ terminal�� �ٲٰ� ����
		if (*key == 0)
			terminal = id;
		else {
			int next = toNumber(*key);
			// �ش� �ڽĳ�尡 ������ �����Ѵ�.
			if (children[next] == NULL)
				children[next] = new TrieNode();
			// �ش� �ڽĳ��� ��� ȣ��
			children[next]->insert(key + 1, id);
		}
	}
	// �� ��带 ��Ʈ���ϴ� Ʈ���̿� ���ڿ� key�� �����Ǵ� ��带 ã�´�. ( �����尡 �ƴϾ ��ȯ�Ѵ�. )
	// ������ NULL�� ��ȯ�Ѵ�.
	TrieNode* find(const char* key) {
		// ���ڿ��� ������ �� ��带 ��ȯ�Ѵ�. ( ���������� �Ű� �Ⱦ� )
		if (*key == 0) return this;
		int next = toNumber(*key);
		// ������ NULL ��ȯ
		if (children[next] == NULL) return NULL;
		return children[next]->find(key + 1);
	}
	// �� ������ Ÿ������ ���� ��, ��ȣ id�� key�� Ÿ�����ϱ� ����
	// �ּ� �� ���� Ű�� �� ������ �ϳ�?
	int type(const char* key, int id) {
		// ���ڿ� �����
		if (*key == 0) return 0;
		// �� ��忡�� ��õ�Ǵ� ���ڿ��� �� ���ڿ��̸� �� ������ ����
		if (first == id) return 1;
		// �ƴϸ� ���� ���ڸ� Ÿ�����Ѵ�.
		int next = toNumber(*key);
		return 1 + children[next]->type(key + 1, id);
	}
};

// ������ ��Ÿ���� Ʈ���̰� �־��� ��, �ܾ� word�� Ÿ�����ϴ� ��
// �� ���̳� Ű�� ������ �ϴ��� ����Ѵ�.
int countKeys(TrieNode* trie, const char* word) {
	// �� ���ڿ��� ������ �ִ��� Ȯ���ϰ�, �ִٸ� ��ȣ�� ���Ѵ�.
	TrieNode* node = trie->find(word);
	// ������ ������ ���� Ÿ������ ���ۿ� ����.
	// node == NULL : Ʈ���̿� �ش� �ܾ ����.
	// node->terminal == -1 : ������ ����.
	if (node == NULL || node->terminal == -1) return strlen(word);
	// Ž���ϸ鼭 Ÿ������ ����� ã�´�.
	return trie->type(word, node->terminal);
}

// �Է¿� �־����� �ܾ���� �����ؼ� Ʈ���̷� ��ȯ�Ѵ�.
// words : �ܾ��� ����
TrieNode* readInput(int words) {
	// �ܾ���� ���� ���� ��������, �ܾ��� ������������ �����Ѵ�.
	vector<pair<int, string>> input;
	for (int i = 0; i < words; ++i) {
		// �ܾ��� �ִ���̴� 10
		char buf[11];
		int freq;
		scanf("%s %d", buf, &freq);
		// �������� ������������ �����ϱ� ���� (-)�� �ٿ��ش�.
		input.push_back(make_pair(-freq, buf));
	}
	sort(input.begin(), input.end());
	
	// �̶� �տ� �ִ� �ܾ��ϼ��� �켱������ ����.
	// �迭�� �ε����� �� �ܾ��� ��ȣ�� ����.
	TrieNode* trie = new TrieNode();
	for (int i = 0; i < input.size(); ++i) {
		trie->insert(input[i].second.c_str(), i);
		cout << input[i].first << ' ';
	}
	// ��Ʈ�� first�� -1�� �ٲ��ش�.
	trie->first = -1;
	return trie;
}


int main() {
	int c;
	cin >> c;
	for (int tn = 1; tn <= c; ++tn) {
		int n, m;
		cin >> n >> m;

		TrieNode* trie = readInput(n);
		int sum = -1;
		for (int i = 0; i < m; ++i) {
			char buf[11];
			scanf("%s", buf);
			sum += 1 + countKeys(trie, buf);
		}
		cout << sum << '\n';
	}
}