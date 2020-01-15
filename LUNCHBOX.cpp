#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

int n;
int hitTime[10000], eatTime[10000];

// 가열시간과 먹는시간을 갖는 구조체
struct food
{
	int hit;
	int eat;

	food(int a, int b) {
		hit = a;
		eat = b;
	}
};

// 먹는 시간을 기준으로 내림차순 정렬
bool compare(food a, food b) {
	return a.eat > b.eat;
}

// 음식들의 정보를 먹는 시간을 기준으로 정렬해서, 먹는데 오래걸리는 사람을 먼저 고름
int solve() {
	int time = 0;
	vector<food> info;
	for (int i = 0; i < n; i++) {
		info.push_back(food(hitTime[i], eatTime[i]));
	}
	sort(info.begin(), info.end(),compare);
	
	time += info[0].hit;
	int tempEat = info[0].eat;
	for (int i = 1; i < n; i++) {
		time += info[i].hit;
		if ((tempEat - info[i].hit) >= info[i].eat)
			tempEat -= info[i].hit;
		else
			tempEat = info[i].eat;
	}
	time += tempEat;

	return time;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		cin >> n;

		for (int i = 0; i < n; i++) {
			cin >> hitTime[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> eatTime[i];
		}

		cout << solve() << "\n";
	}
}