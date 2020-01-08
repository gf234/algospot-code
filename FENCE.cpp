#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> h;

int solve(int left, int right) {
	if (left == right) return h[left];

	int mid = (left + right) / 2;

	int ret = max(solve(left, mid), solve(mid + 1, right));

	// 중간에 너비가 2인 사각형부터 고려
	int lo = mid, hi = mid + 1;
	int height = min(h[lo], h[hi]);
	ret = max(ret, height * 2);

	// 오른쪽이나 왼쪽으로 확장
	while (left < lo || hi < right) {
		// 오른쪽으로 확장하는 경우
		if (hi < right && (lo == left || h[lo - 1] < h[hi + 1])) {
			++hi;
			height = min(height, h[hi]);
		}
		// 왼쪽으로 확장하는 경우
		else {
			--lo;
			height = min(height, h[lo]);
		}
		ret = max(ret, height * (hi - lo + 1));
	}
	return ret;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		int n;
		cin >> n;
		
		for (int i = 0; i < n; i++) {
			int temp;
			cin >> temp;

			h.push_back(temp);
		}

		cout << solve(0, n - 1) << "\n";
		h.clear();
	}
}