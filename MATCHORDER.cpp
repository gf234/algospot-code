#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

int n;
int rusTeam[100];
vector<int> korTeam;

// �̱� �� �ִ°�� ���� ���� ���̷� �̱�°��� �����ϰ�, �̱� �� ���� ��� ���� ���ϴ� �ָ� ����
int solve() {
	int cnt = 0;
	for (int rusPos = 0; rusPos < n; rusPos++) {
		if (rusTeam[rusPos] <= korTeam.back()) {
			int minWin = korTeam.size() - 1;
			for (int i = korTeam.size() - 2; i >= 0; i--) {
				if (rusTeam[rusPos] <= korTeam[i])
					minWin = i;
				else
					break;
			}
			cnt++;
			korTeam.erase(korTeam.begin() + minWin);
		}
		else {
			korTeam.erase(korTeam.begin());
		}
	}
	return cnt;
}

int main() {
	int testCase;
	cin >> testCase;
	for (int caseNum = 1; caseNum <= testCase; caseNum++) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> rusTeam[i];
		}
		for (int i = 0; i < n; i++) {
			int temp;
			cin >> temp;
			korTeam.push_back(temp);
		}
		sort(korTeam.begin(), korTeam.end());

		cout << solve() << "\n";
		korTeam.clear();
	}
}