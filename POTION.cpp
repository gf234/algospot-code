#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
// ��Ŭ���� �˰��� : �ִ� ����� ã��
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}
// a/b ���� ���ų� ū �ּ��� �ڿ��� ��ȯ
int ceil(int a, int b) {
	return (a + b - 1) / b;
}
// �����ǿ� �̹� ���� ������ �־����� �� ���� ����� ���� ��ȯ
vector<int> solve(const vector<int>& recipe, const vector<int>& put) {
	int n = recipe.size();
	// �����ǵ��� �ִ� ������� ���Ѵ�.
	int b = recipe[0];
	for (int i = 1; i < n; ++i) b = gcd(b, recipe[i]);

	int a = b;
	// a <= x * b = put[i] * b / recipe[i] --> õ���Լ��� ����
	for (int i = 0; i < n; ++i)
		a = max(a, ceil(put[i] * b, recipe[i]));
	// a/b�� �з��� ����� ��
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