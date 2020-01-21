#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

int n;
double dist[101][101];
vector<pair<double, double>> locations;

bool decision(double d) {
	vector<bool> visited(n, false);
	visited[0] = true;
	queue<int> q;
	q.push(0);
	int seen = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		++seen;
		for(int there = 0; there<n;++there)
			if (!visited[there] && dist[here][there] <= d) {
				visited[there] = true;
				q.push(there);
			}
	}
	return seen == n;
}

double optimize() {
	double lo = 0, hi = 1416.00;
	for (int it = 0; it < 100; ++it) {
		double mid = (lo + hi) / 2;
		if (decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}

double calDist(pair<double, double> a, pair<double, double> b) {
	return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		locations.clear();
		cin >> n;
		for (int i = 0; i < n; ++i) {
			double a, b;
			cin >> a >> b;
			locations.push_back(make_pair(a, b));
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				dist[i][j] = calDist(locations[i], locations[j]);
			}
		}
		double result = optimize();
		printf("%.2f\n", result);
	}
}