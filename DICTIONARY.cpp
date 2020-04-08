#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
using namespace std;

// ���ĺ��� �� ���ڿ� ���� ���� ��� ǥ��
// ���� (i,j)�� ���ĺ� i�� j���� �տ� �;� ���� ��Ÿ����.
vector<vector<int>> adj;
//�־��� �ܾ��κ��� ���ĺ� ���� ���İ��� �׷����� �����Ѵ�.
void makeGraph(const vector<string>& words) {
	// �ʱ�ȭ ��� : ex) vector<int>(����, ���� �Ұ���)
	adj = vector<vector<int>>(26, vector<int>(26, 0));
	for (int j = 1; j < words.size(); ++j) {
		// len = �� ª�� �ܾ��� ����
		int i = j - 1, len = min(words[i].size(), words[j].size());
		// word[i]�� word[j]�տ� ���� ������ ã�´�.
		for(int k = 0; k<len; ++k)
			if (words[i][k] != words[j][k]) {
				int a = words[i][k] - 'a';
				int b = words[j][k] - 'a';
				adj[a][b] = 1;
				break;
			}
	}
}

vector<int> seen, order;
void dfs(int here) {
	seen[here] = 1;
	for (int there = 0; there < adj.size(); ++there)
		if (adj[here][there] && !seen[there])
			dfs(there);
	order.push_back(here);
}
// adj�� �־��� �׷����� ���������� ����� ��ȯ�Ѵ�.
// �׷����� DAG�� �ƴ϶�� �� ���͸� ��ȯ�Ѵ�.
vector<int> topologicalSort() {
	int m = adj.size();
	seen = vector<int>(m, 0);
	order.clear();
	for (int i = 0; i < m; ++i) if (!seen[i]) dfs(i);
	reverse(order.begin(), order.end());
	// ���� �׷����� DAG�� �ƴ϶�� ���� ����� ������ ������ �ִ�.
	for (int i = 0; i < m; ++i)
		for (int j = i + 1; j < m; ++j)
			if (adj[order[j]][order[i]])
				return vector<int>();
	// ���� ����� ���� �켱 Ž������ ���� ������ ��ȯ�Ѵ�.
	return order;
}


int main() {
	int c;
	cin >> c;
	for (int testN = 1; testN <= c; ++testN) {
		int n;
		cin >> n;

		vector<string> words(n);
		for (int i = 0; i < n; ++i)
			cin >> words[i];

		makeGraph(words);

		vector<int> result = topologicalSort();

		if (result.empty())
			cout << "INVALID HYPOTHESIS";
		else
			for (int i = 0; i < result.size(); ++i)
				cout << (char)(result[i]+'a');
		cout << '\n';
	}
}