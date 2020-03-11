#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;

int n, a, b;

struct RNG {
	int seed, a, b;
	RNG(int _a, int _b) : a(_a), b(_b), seed(1983) {}
	// 다음 난수 생성
	int next() {
		int ret = seed;
		// 오버플로우 방지를 위해 (long long)으로 캐스팅
		seed = ((seed * (long long)a) + b) % 20090711;
		return ret;
	}
};

int runningMedian(int n, RNG rng) {
	priority_queue<int, vector<int>, less<int>>maxHeap;
	priority_queue<int, vector<int>, greater<int>>minHeap;
	int ret = 0;

	// 반복문 불변식
	// 1 : maxHeap의 크기는 minHeap의 크기와 같거나 1 크다.
	// 2 : maxHeap.top() <= minHeap.top()
	for (int cnt = 1; cnt <= n; ++cnt) {
		// 1번 불변식 부터 만족 시킨다.
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());
		// 2번 불변식이 깨졌을 경우 두 힙의 루트를 스왑해서 복구 시킨다.
		if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()) {
			int a = maxHeap.top(), b = minHeap.top();
			maxHeap.pop(); minHeap.pop();
			maxHeap.push(b);
			minHeap.push(a);
		}
		ret = (ret + maxHeap.top()) % 20090711;
	}
	return ret;
}

int main() {
	int c;
	cin >> c;
	for (int testN = 1; testN <= c; ++testN) {
		cin >> n >> a >> b;
		
		int result = runningMedian(n, RNG(a, b));
		cout << result << '\n';
	}
}