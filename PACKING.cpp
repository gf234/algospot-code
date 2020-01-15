#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

int n, w;

// ������ ���� ������ Ŭ����
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

// weight ��ŭ �������� itemNum�� ������ ����
int cache[1001][101];
int pack(int weight, int itemNum) {
	if (itemNum == n) return 0;
		
	int& ret = cache[weight][itemNum];
	if (ret != -1) return ret;
	
	// �ȴ������
	ret = pack(weight, itemNum + 1);
	// �������
	if (weight >= itemList[itemNum].size) {
		ret = max(ret, pack(weight - itemList[itemNum].size, itemNum + 1) + itemList[itemNum].rate);
	}

	return ret;
}

// ���� �籸��
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
		// �Է� �ޱ� 
		cin >> n >> w;
		for (int i = 0; i < n; i++) {
			string name; int size; int rate;
			cin >> name >> size >> rate;
			item temp = item(name, size, rate);
			itemList.push_back(temp);
		}
		memset(cache, -1, sizeof(cache));

		// �Լ� ����
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