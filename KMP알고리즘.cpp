#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

vector<int> getPartialMatch(const string& N);

// H의 부분 문자열로 N이 출현하는 시작 위치들을 모두 반환한다.
vector<int> kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	vector<int> ret;
	// pi[i] : N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
	vector<int> pi = getPartialMatch(N);
	// begin = matched = 0에서부터 시작
	int begin = 0, matched = 0;
	while (begin <= n - m) {
		// 만약 H의 해당 글자와 N의 해당 글자가 같다면
		if (matched < m && H[begin + matched] == N[matched]) {
			++matched;
			// 결과적으로 m글자가 모두 일치하면 답에 추가
			if (matched == m) ret.push_back(begin);
		}
		else {
			// 하나도 같지 않은 경우 다음 칸에서부터 계속
			if (matched == 0)
				++begin;
			else {
				begin += matched - pi[matched - 1];
				// 이동해도 이미 일치하기 때문에 처음부터 할 필요가 없다.
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}

int main() {
	
}