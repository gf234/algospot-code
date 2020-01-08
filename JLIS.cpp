#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const long long NEGINF = numeric_limits<long long>::min();
int n, m;
int A[100], B[100];


int cache[101][101];
int solve(int indexA, int indexB) {
	int& ret = cache[indexA+1][indexB+1];
	if (ret != -1)
		return ret;
	
	ret = 2;
	long long a = (indexA == -1 ? NEGINF : A[indexA]);
	long long b = (indexB == -1 ? NEGINF : B[indexB]);
	long long maxElement = max(a, b);

	for (int nextA = indexA + 1; nextA < n; ++nextA) 
		if (maxElement < A[nextA])
			ret = max(ret, solve(nextA, indexB)+1);
	for (int nextB = indexB + 1; nextB < m; ++nextB)
		if (maxElement < B[nextB])
			ret = max(ret, solve(indexA, nextB)+1);

	return ret;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		cin >> n >> m;
		for (int i = 0; i < n; i++) {
			cin >> A[i];
		}
		for (int i = 0; i < m; i++) {
			cin >> B[i];
		}
		
		memset(cache, -1, sizeof(cache));
		cout << solve(-1,-1) -2 << "\n";
	}
}