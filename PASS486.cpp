#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

const int TM = 1000 * 1000 * 10;
// minFactor[i] : i의 가장 작은 소인수 ( 소수는 자신 )
// minFactorPower[i] : i의 가장 작은 소인수의 지수
int minFactor[TM + 1];
int minFactorPower[TM + 1];
// 에라토스테네스의 체를 이용해 소인수 구하기
void eratosthenes() {
	minFactor[0] = minFactor[1] = -1;

	for (int i = 2; i <= TM; ++i)
		minFactor[i] = i;

	int sqrtn = int(sqrt(TM));
	for (int i = 2; i <= sqrtn; ++i) {
		if (minFactor[i] == i) {
			for (int j = i * i; j <= TM; j += i)
				if (minFactor[j] == j)
					minFactor[j] = i;
		}
	}
}
// factors[i] : i가 가진 약수의 수
int factors[TM + 1];
void getFactorSmart() {
	factors[1] = 1;
	for (int n = 2; n <= TM; ++n) {
		// 소수인 경우
		if (minFactor[n] == n) {
			minFactorPower[n] = 1;
			factors[n] = 2;
		}
		// 아닌 경우
		else {
			int p = minFactor[n];
			int m = n / p;
			// p의 지수가 1인 경우
			if (p != minFactor[m])
				minFactorPower[n] = 1;
			else
				minFactorPower[n] = minFactorPower[m] + 1;
			int a = minFactorPower[n];
			factors[n] = (factors[m] / a) * (a + 1);
		}
	}
}

int main(int argc, char** argv)
{
	eratosthenes();
	getFactorSmart();
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int n, lo, hi;
		cin >> n >> lo >> hi;

		int cnt = 0;
		for (int i = lo; i <= hi; ++i) {
			if (factors[i] == n)
				cnt++;
		}
		cout << cnt << "\n";
	}
	return 0;
}