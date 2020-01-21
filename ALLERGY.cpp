#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

// n : 친구의 수, m : 만들 수 있는 음식의 수
int n, m;
vector<string> name;
// eaters[food] : 해당 음식을 먹을 수 있는 친구들의 집합
// canEat[friend] : 해당 친구가 먹을 수 있는 음식의 집합
vector<int> canEat[50], eaters[50];

int best;

// 음식마다 고를지 말지 결정해서 완전탐색
// food : 이번에 결정할 음식 번호
// edible[i] : 지금까지 고른 음식 중 i번 친구가 먹을 수 있는 음식의 수
// chosen : 지금까지 고른 음식의 수
void slowSearch(int food, vector<int>& edible, int chosen) {
	// 간단한 가지치기
	if (chosen >= best) return;
	//기저사례:모든 음식에 대해 만들지 결정했으면, 모두 먹을 수 있는지 확인
	// find() 함수는 찾는 값이 없는 경우 end를 가리킴...
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
// edible[friend] : 현재까지 고른 음식 중 friend가 먹을 수 있는 음식의 수 
// chosen : 지금까지 고른 음식의 수
void search(vector<int>& edible, int chosen) {
	// 간단한 가지치기
	if (chosen >= best) return;
	// 먹을 수 있는게 없는 친구 찾기
	int first = 0;
	while (first < n && edible[first] > 0) ++first;
	// 다 먹을 수 있는 경우 종료
	if (first == n) {
		best = chosen;
		return;
	}
	// 이 친구가 먹을 수 있는 음식을 만든다
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