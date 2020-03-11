#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

string str;

bool wellMatched() {
	// 여는 괄호 문자들과 닫는 괄호 문자들
	const string opening("({["), closing(")}]");
	// 열린 괄호들을 순서대로 담을 스택
	stack<char> openStack;
	for (int i = 0; i < str.size(); ++i)
		// 여는 괄호인지 닫는 괄호인지 확인한다.
		if (opening.find(str[i]) != -1)
		openStack.push(str[i]);
		else {
			//스택이 비어있으면 실패
			if (openStack.empty()) return false;
			// 순서대로 짝이 맞지 않으면 실패
			if (opening.find(openStack.top()) != closing.find(str[i]))
				return false;
			// 짝을 맞춘 괄호는 스택에서 제거
			openStack.pop();
		}
	// 남은 괄호가 없으면 완료 ( 짝이 다 맞았다는 뜻 )
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