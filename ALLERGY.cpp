#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

// n : ģ���� ��, m : ���� �� �ִ� ������ ��
int n, m;
vector<string> name;
// eaters[food] : �ش� ������ ���� �� �ִ� ģ������ ����
// canEat[friend] : �ش� ģ���� ���� �� �ִ� ������ ����
vector<int> canEat[50], eaters[50];

int best;

// ���ĸ��� ���� ���� �����ؼ� ����Ž��
// food : �̹��� ������ ���� ��ȣ
// edible[i] : ���ݱ��� �� ���� �� i�� ģ���� ���� �� �ִ� ������ ��
// chosen : ���ݱ��� �� ������ ��
void slowSearch(int food, vector<int>& edible, int chosen) {
	// ������ ����ġ��
	if (chosen >= best) return;
	//�������:��� ���Ŀ� ���� ������ ����������, ��� ���� �� �ִ��� Ȯ��
	// find() �Լ��� ã�� ���� ���� ��� end�� ����Ŵ...
	if (food == m) {
		if (find(edible.begin(), edible.end(), 0) == edible.end())
			best = chosen;
		return;
	}
	
	slowSearch(food + 1, edible, chosen);

	for (int j = 0; j < eaters[food].size(); ++j) {
		edible[eaters[food][j]]++;
	}
	slowSearch(food + 1, edible, chosen + 1);
	for (int j = 0; j < eaters[food].size(); ++j) {
		edible[eaters[food][j]]--;
	}
}
int cnt=0;
// edible[friend] : ������� �� ���� �� friend�� ���� �� �ִ� ������ �� 
// chosen : ���ݱ��� �� ������ ��
void search(vector<int>& edible, int chosen) {
	// ������ ����ġ��
	if (chosen >= best) return;
	// ���� �� �ִ°� ���� ģ�� ã��
	int first = 0;
	while (first < n && edible[first] > 0) ++first;
	// �� ���� �� �ִ� ��� ����
	if (first == n) {
		best = chosen;
		return;
	}
	// �� ģ���� ���� �� �ִ� ������ �����
	for (int i = 0; i < canEat[first].size(); ++i) {
		int food = canEat[first][i];
		for (int j = 0; j < eaters[food].size(); ++j)
			edible[eaters[food][j]]++;
		search(edible, chosen + 1);
		for (int j = 0; j < eaters[food].size(); ++j) 
			edible[eaters[food][j]]--;
	}
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		name.clear();
		for (int i = 0; i < 50; i++) {
			eaters[i].clear();
			canEat[i].clear();
		}
		cin >> n >> m;
		for (int i = 0; i < n; i++) {
			string temp;
			cin >> temp;
			name.push_back(temp);
		}
		for (int i = 0; i < m; i++) {
			int temp;
			cin >> temp;
			for (int j = 0; j < temp; j++) {
				string eater;
				cin >> eater;
				for (int k = 0; k < n; k++) {
					if (eater == name[k]) {
						eaters[i].push_back(k);
						canEat[k].push_back(i);
					}
				}
			}
		}
		best = 987654321;

		vector<int> edible(n);
		search(edible, 0);
		cout << best << "\n";

	}
}