#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 987654321;

vector<vector<int>> vSwitch = { {0,1,2},{3,7,9,11},{4,10,14,15},{0,4,5,6,7},{6,7,8,10,12}, {0,2,14,15},{3,14,15},{4,5,7,14,15},{1,2,3,4,5},{3,4,5,9,13} };

void change(vector<int>& clock, int n) {
	for (int i = 0; i < vSwitch[n].size(); i++) {
		if ((clock[vSwitch[n][i]] += 3) == 15) {
			clock[vSwitch[n][i]] = 3;
		}
	}
}

bool is_finish(vector<int> clock) {
	for (int i = 0; i < 16; i++) {
		if (clock[i] != 12) return false;
	}
	return true;
}

// 0번 스위치 부터 시작
int solve(vector<int> clock, int swN) {
	if (swN == 10) return is_finish(clock) ?  0 :  INF;

	int ret = INF;
	// 한 스위치 당 0~3번까지 확인
	for (int i = 0; i < 4; i++) {
		ret = min(ret, i + solve(clock, swN + 1));
		change(clock, swN);
	}
	// 4번 눌리면 원래와 같은 상태가 됨
	return ret;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		vector<int> clock;
	
		for (int i = 0; i < 16; i++) {
			int temp;
			cin >> temp;
			clock.push_back(temp);
		}

		vector<int> pushN(10, 0);
		
		int temp = solve(clock, 0);
		if (temp == INF) temp = -1;
		cout << temp << "\n";
	}
}