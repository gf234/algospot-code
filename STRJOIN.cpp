#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

int n;
vector<int> lengths;

// 작은것 먼저 합치기
int solve() {
	int total = 0;
	for (int i = 0; i < n - 1; i++) {
		int temp = lengths[0] + lengths[1];
		total += temp;
		lengths.erase(lengths.begin());
		lengths[0] = temp;
		// 다시 정렬
		sort(lengths.begin(), lengths.end());
		
	}
	return total;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			int temp;
			cin >> temp;
			lengths.push_back(temp);
		}
		sort(lengths.begin(), lengths.end());

		cout << solve() << "\n";
		lengths.clear();
	}
}