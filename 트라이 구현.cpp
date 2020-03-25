#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <string>
using namespace std;

const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; }

// 트라이의 노드 구조체
struct TrieNode {
	TrieNode* children[ALPHABETS];
	// 이 노드에서 종료하는 문자열의 번호. 없으면 -1
	int terminal;
	// 이 노드를 루트로 하는 트라이에 가장 먼저 추가된 단어의 번호. -1로 초기화
	int first;
	// 이 노드를 루트로하는 트라이에 번호 id인 문자열 key를 추가한다.
	void insert(const char* key, int id) {
		// first를 우선 갱신
		if (first == -1) first = id;
		// 문자열이 끝나면 terminal만 바꾸고 종료
		if (*key == 0)
			terminal = id;
		else {
			int next = toNumber(*key);
			// 해당 자식노드가 없으면 생성한다.
			if (children[next] == NULL)
				children[next] = new TrieNode();
			// 해당 자식노드로 재귀 호출
			children[next]->insert(key + 1, id);
		}
	}
	// 이 노드를 루트로하는 트라이에 문자열 key와 대응되는 노드를 찾는다. ( 종료노드가 아니어도 반환한다. )
	// 없으면 NULL을 반환한다.
	TrieNode* find(const char* key) {
		// 문자열이 끝나면 이 노드를 반환한다. ( 종료노드인지 신경 안씀 )
		if (*key == 0) return this;
		int next = toNumber(*key);
		// 없으면 NULL 반환
		if (children[next] == NULL) return NULL;
		return children[next]->find(key + 1);
	}
	// 이 노드까지 타이핑해 왔을 때, 번호 id인 key를 타이핑하기 위해
	// 최소 몇 번의 키를 더 눌러야 하나?
	int type(const char* key, int id) {
		// 문자열 종료시
		if (*key == 0) return 0;
		// 이 노드에서 추천되는 문자열이 이 문자열이면 탭 누르고 종료
		if (first == id) return 1;
		// 아니면 다음 문자를 타이핑한다.
		int next = toNumber(*key);
		return 1 + children[next]->type(key + 1, id);
	}
};

// 사전을 나타내는 트라이가 주어질 때, 단어 word를 타이핑하는 데
// 몇 번이나 키를 눌러야 하는지 계산한다.
int countKeys(TrieNode* trie, const char* word) {
	// 이 문자열이 사전에 있는지 확인하고, 있다면 번호를 구한다.
	TrieNode* node = trie->find(word);
	// 사전에 없으면 직접 타이핑할 수밖에 없다.
	// node == NULL : 트라이에 해당 단어가 없다.
	// node->terminal == -1 : 사전에 없다.
	if (node == NULL || node->terminal == -1) return strlen(word);
	// 탐색하면서 타이핑할 방법을 찾는다.
	return trie->type(word, node->terminal);
}

// 입력에 주어지는 단어들을 정렬해서 트라이로 변환한다.
// words : 단어의 개수
TrieNode* readInput(int words) {
	// 단어들을 출현 빈도의 내림차순, 단어의 오름차순으로 정렬한다.
	vector<pair<int, string>> input;
	for (int i = 0; i < words; ++i) {
		// 단어의 최대길이는 10
		char buf[11];
		int freq;
		scanf("%s %d", buf, &freq);
		// 출현빈도의 내림차순으로 정렬하기 위해 (-)를 붙여준다.
		input.push_back(make_pair(-freq, buf));
	}
	sort(input.begin(), input.end());
	
	// 이때 앞에 있는 단어일수록 우선순위가 높다.
	// 배열의 인덱스를 각 단어의 번호로 쓰자.
	TrieNode* trie = new TrieNode();
	for (int i = 0; i < input.size(); ++i) {
		trie->insert(input[i].second.c_str(), i);
		cout << input[i].first << ' ';
	}
	// 루트의 first를 -1로 바꿔준다.
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