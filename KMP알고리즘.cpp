#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

vector<int> getPartialMatch(const string& N);

// H�� �κ� ���ڿ��� N�� �����ϴ� ���� ��ġ���� ��� ��ȯ�Ѵ�.
vector<int> kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	vector<int> ret;
	// pi[i] : N[..i]�� ���̻絵 �ǰ� ���λ絵 �Ǵ� ���ڿ��� �ִ� ����
	vector<int> pi = getPartialMatch(N);
	// begin = matched = 0�������� ����
	int begin = 0, matched = 0;
	while (begin <= n - m) {
		// ���� H�� �ش� ���ڿ� N�� �ش� ���ڰ� ���ٸ�
		if (matched < m && H[begin + matched] == N[matched]) {
			++matched;
			// ��������� m���ڰ� ��� ��ġ�ϸ� �信 �߰�
			if (matched == m) ret.push_back(begin);
		}
		else {
			// �ϳ��� ���� ���� ��� ���� ĭ�������� ���
			if (matched == 0)
				++begin;
			else {
				begin += matched - pi[matched - 1];
				// �̵��ص� �̹� ��ġ�ϱ� ������ ó������ �� �ʿ䰡 ����.
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}

int main() {
	
}