#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

// n : 마을개수
// d : 지난 일수
// p : 교도소 번호
// t : 확률을 계산할 마을의 수
int n, d, p, t;

// A : 마을간 길 정보
int A[50][50];

// Q : 확률 계산해야하는 마을들 리스트
vector<int> Q;

// 인접 마을 찾는 함수
vector<int> findNeighbor(int vilNum) {
	vector<int> temp;
	for (int j = 0; j < n; j++) 
		if (A[vilNum][j] == 1)
			temp.push_back(j);
	return temp;
}

// days만큼 지났을때 vilNum의 확률
double cache[101][51];
double solve(int days, int vilNum) {
	// 기저 사례 : 0일 지났을때 교도소인지 확인
	if (days == 0) return vilNum == p ? 1 : 0;

	double& ret = cache[days][vilNum];
	if (ret != -1) return ret;
	ret = 0;

	vector<int> neighbor = findNeighbor(vilNum);
	for (int i = 0; i < neighbor.size(); i++) {
		vector<int> nn = findNeighbor(neighbor[i]);
		ret += solve(days - 1, neighbor[i]) / nn.size();
	}
	return ret;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		// 초기화 코드
		cin >> n >> d >> p;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> A[i][j];
			}
		}
		cin >> t;
		for (int i = 0; i < t; i++) {
			int temp;
			cin >> temp;
			Q.push_back(temp);
		}
		fill(&cache[0][0], &cache[100][51], -1);

		// 마을마다 확률 계산
		for (int i = 0; i < Q.size(); i++) {
			printf("%.8lf ", solve(d, Q[i]));
		}
		cout << "\n";

		Q.clear();
	}
}