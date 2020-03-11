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
	// ���� ���� ����
	int next() {
		int ret = seed;
		// �����÷ο� ������ ���� (long long)���� ĳ����
		seed = ((seed * (long long)a) + b) % 20090711;
		return ret;
	}
};

int runningMedian(int n, RNG rng) {
	priority_queue<int, vector<int>, less<int>>maxHeap;
	priority_queue<int, vector<int>, greater<int>>minHeap;
	int ret = 0;

	// �ݺ��� �Һ���
	// 1 : maxHeap�� ũ��� minHeap�� ũ��� ���ų� 1 ũ��.
	// 2 : maxHeap.top() <= minHeap.top()
	for (int cnt = 1; cnt <= n; ++cnt) {
		// 1�� �Һ��� ���� ���� ��Ų��.
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());
		// 2�� �Һ����� ������ ��� �� ���� ��Ʈ�� �����ؼ� ���� ��Ų��.
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