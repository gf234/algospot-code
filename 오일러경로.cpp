#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
using namespace std;

// �׷����� ���� ��� ǥ��. adj[i][j] = i�� j������ ������ ��
vector<vector<int>> adj;
// graph[i][j] = i�� �����ؼ� j�� ������ �ܾ��� ���
vector<string> graph[26][26];
// 
// ���� �׷����� ���� ��� adj�� �־��� �� ���Ϸ� ��Ŷ�� ����Ѵ�.
// ����� ������� circuit�� �������� ���Ϸ� ��Ŷ�� �ȴ�.
void getEulerCircuit(int here, vector<int>& circuit) {
	for(int there = 0; there<adj[here].size(); ++there)
		while (adj[here][there] > 0) {
			adj[here][there]--; // ���� ������ ��� �����.
			adj[there][here]--;
			getEulerCircuit(there, circuit);
		}
	circuit.push_back(here);
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