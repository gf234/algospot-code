#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
// 유클리드 알고리즘 : 최대 공약수 찾기
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}
// a/b 보다 같거나 큰 최소의 자연수 반환
int ceil(int a, int b) {
	return (a + b - 1) / b;
}
// 레시피와 이미 넣은 정보가 주어질때 더 넣을 재료의 양을 반환
vector<int> solve(const vector<int>& recipe, const vector<int>& put) {
	int n = recipe.size();
	// 레시피들의 최대 공약수를 구한다.
	int b = recipe[0];
	for (int i = 1; i < n; ++i) b = gcd(b, recipe[i]);

	int a = b;
	// a <= x * b = put[i] * b / recipe[i] --> 천장함수로 구현
	for (int i = 0; i < n; ++i)
		a = max(a, ceil(put[i] * b, recipe[i]));
	// a/b배 분량을 만들면 됨
	vector<int> ret(n);
	for (int i = 0; i < n; ++i)
		ret[i] = recipe[i] * a / b - put[i];
	return ret;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int n;
		cin >> n;
		vector<int> recipe, put;
		for (int i = 0; i < n; ++i) {
			int temp;
			cin >> temp;
			recipe.push_back(temp);
		}
		for (int i = 0; i < n; ++i) {
			int temp;
			cin >> temp;
			put.push_back(temp);
		}
		vector<int> result = solve(recipe, put);

		for (int i = 0; i < n; ++i)
			cout << result[i] << " ";
		cout << "\n";
	}
	return 0;
}