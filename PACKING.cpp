#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

int n, w;

// 아이템 정보 저장할 클래스
class item {
public:
	string name;
	int size;
	int rate;

	item(string a, int b, int c) {
		name = a;
		size = b;
		rate = c;
	}
};
vector<item> itemList;

// weight 만큼 남았을때 itemNum을 담을지 말지
int cache[1001][101];
int pack(int weight, int itemNum) {
	if (itemNum == n) return 0;
		
	int& ret = cache[weight][itemNum];
	if (ret != -1) return ret;
	
	// 안담았을때
	ret = pack(weight, itemNum + 1);
	// 담았을때
	if (weight >= itemList[itemNum].size) {
		ret = max(ret, pack(weight - itemList[itemNum].size, itemNum + 1) + itemList[itemNum].rate);
	}

	return ret;
}

// 정답 재구성
void reconstruct(int weight, int itemNum, vector<string>& picked) {
	if (itemNum == n) return;
	if (pack(weight, itemNum) == pack(weight, itemNum + 1)) {
		reconstruct(weight, itemNum + 1, picked);
	}
	else {
		item temp = itemList[itemNum];
		picked.push_back(temp.name);
		reconstruct(weight - temp.size, itemNum + 1, picked);
	}
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		// 입력 받기 
		cin >> n >> w;
		for (int i = 0; i < n; i++) {
			string name; int size; int rate;
			cin >> name >> size >> rate;
			item temp = item(name, size, rate);
			itemList.push_back(temp);
		}
		memset(cache, -1, sizeof(cache));

		// 함수 실행
		int rateMax = pack(w, 0);

		vector<string> picked;
		reconstruct(w, 0, picked);

		printf("%d %d\n", rateMax, picked.size());
		for (int i = 0; i < picked.size(); i++) {
			cout << picked[i] << "\n";
		}

		itemList.clear();
	}
}