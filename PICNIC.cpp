#include <iostream>
#include <vector>
using namespace std;

struct friends {
	int a;
	int b;

	void sort() {
		if (a > b) {
			int temp = a;
			a = b;
			b = temp;
		}
	}
};

int cnt=0;

void choose(int n, vector<friends> vFriends, vector<friends>& picked) {
	// 다 고른 경우
	if (n == (picked.size() * 2)) {
		cnt++;
		return;
	}
	// 아직 짝이 없는 애들 중에서 고르기
	for (int i = 0; i < vFriends.size(); i++) {
		friends temp;
		temp = vFriends[i];
		bool bContinue = false;
		for (int j = 0; j < picked.size(); j++) {
			if ((picked[j].a == temp.a || picked[j].a == temp.b || picked[j].b == temp.a || picked[j].b == temp.b) || (picked.back().a > temp.a)) {
				bContinue = true;
				break;
			}
		}
		if (bContinue) continue;
		picked.push_back(temp);
		choose(n, vFriends, picked);
		picked.pop_back();
	}
	return;
}

int main() {
	int testN;
	cin >> testN;

	for (int testCase = 1; testCase <= testN; testCase++) {
		int n, m;
		cin >> n >> m;

		vector<friends> vFriends;
		for (int i = 0; i < m; i++) {
			friends temp;
			cin >> temp.a >> temp.b;
			temp.sort();
			vFriends.push_back(temp);
		}
		vector<friends> picked;
		choose(n, vFriends, picked);
		cout << cnt << "\n";
		cnt = 0;
	}
}