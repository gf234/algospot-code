#include <iostream>
#include <string>
using namespace std;


string reverse(string::iterator& it) {
	char head = *it;
	++it;
	if (head == 'b' || head == 'w')
		return string(1, head);
	string upperLeft = reverse(it);
	string upperRight = reverse(it);
	string lowerLeft = reverse(it);
	string lowerRight = reverse(it);
	// ���� ���� �Ʒ� �������� ��ġ �ٲٱ�.
	return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}

int main() {
	int testN;
	cin >> testN;
	for (int testCase = 1; testCase <= testN; testCase++) {
		string pic;
		cin >> pic;

		string::iterator it = pic.begin();

		cout << reverse(it) << "\n";
	}
}