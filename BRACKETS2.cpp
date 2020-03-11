#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

string str;

bool wellMatched() {
	// ���� ��ȣ ���ڵ�� �ݴ� ��ȣ ���ڵ�
	const string opening("({["), closing(")}]");
	// ���� ��ȣ���� ������� ���� ����
	stack<char> openStack;
	for (int i = 0; i < str.size(); ++i)
		// ���� ��ȣ���� �ݴ� ��ȣ���� Ȯ���Ѵ�.
		if (opening.find(str[i]) != -1)
		openStack.push(str[i]);
		else {
			//������ ��������� ����
			if (openStack.empty()) return false;
			// ������� ¦�� ���� ������ ����
			if (opening.find(openStack.top()) != closing.find(str[i]))
				return false;
			// ¦�� ���� ��ȣ�� ���ÿ��� ����
			openStack.pop();
		}
	// ���� ��ȣ�� ������ �Ϸ� ( ¦�� �� �¾Ҵٴ� �� )
	return openStack.empty();
}

int main() {
	int testCase;
	cin >> testCase;
	for (int testNum = 1; testNum <= testCase; ++testNum) {
		cin >> str;

		if (wellMatched())
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}