#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

// n : ��������
// d : ���� �ϼ�
// p : ������ ��ȣ
// t : Ȯ���� ����� ������ ��
int n, d, p, t;

// A : ������ �� ����
int A[50][50];

// Q : Ȯ�� ����ؾ��ϴ� ������ ����Ʈ
vector<int> Q;

// ���� ���� ã�� �Լ�
vector<int> findNeighbor(int vilNum) {
	vector<int> temp;
	for (int j = 0; j < n; j++) 
		if (A[vilNum][j] == 1)
			temp.push_back(j);
	return temp;
}

// days��ŭ �������� vilNum�� Ȯ��
double cache[101][51];
double solve(int days, int vilNum) {
	// ���� ��� : 0�� �������� ���������� Ȯ��
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
		// �ʱ�ȭ �ڵ�
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

		// �������� Ȯ�� ���
		for (int i = 0; i < Q.size(); i++) {
			printf("%.8lf ", solve(d, Q[i]));
		}
		cout << "\n";

		Q.clear();
	}
}