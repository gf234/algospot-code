#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

// ������ų ���ڵ�
vector<string> words;

// ã���� ����� ���� �ϳ��� ���ϵ�ī�� ����
string w, s;
int cache[101][101];

int find(int wn, int sn) {
	int& ret = cache[wn][sn];
	if (ret != -1) return ret;

	while (sn < s.size() && wn < w.size() && (w[wn] == '?' || w[wn] == s[sn])) {
		++wn;
		++sn;
	}

	if (wn == w.size())
		return ret = (sn == s.size());
	
	if(w[wn] == '*')
		for (int skip = 0; sn + skip <= s.size(); ++skip) 
			if (find(wn+1, sn+skip))
				return ret = 1;
	
	return ret = 0;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		cin >> w;

		int n;
		cin >> n;

		for (int i = 0; i < n; i++) {
			string temp;
			cin >> temp;
			words.push_back(temp);
		}
		// �ƽ�Ű�ڵ�� ����
		sort(words.begin(), words.end(), less<string>());
		memset(cache, -1, sizeof(cache));

		
		for (int i = 0; i < n; i++) {
			s = words[i];
			if (find(0, 0))
				cout << words[i] << "\n";
			memset(cache, -1, sizeof(cache));
		}
		words.clear();
	}
}