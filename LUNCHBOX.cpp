#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

int n;
int hitTime[10000], eatTime[10000];

// �����ð��� �Դ½ð��� ���� ����ü
struct food
{
	int hit;
	int eat;

	food(int a, int b) {
		hit = a;
		eat = b;
	}
};

// �Դ� �ð��� �������� �������� ����
bool compare(food a, food b) {
	return a.eat > b.eat;
}

// ���ĵ��� ������ �Դ� �ð��� �������� �����ؼ�, �Դµ� �����ɸ��� ����� ���� ��
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