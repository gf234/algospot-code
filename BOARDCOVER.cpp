#include <iostream>
#include <vector>
using namespace std;

// 4���� ����� ��
const int coverType[4][3][2]{
	{{0,0},{1,0},{0,1}},
	{{0,0},{0,1},{1,1}},
	{{0,0},{1,0},{1,1}},
	{{0,0},{1,0},{1,-1}}
};

bool set(vector<vector<int>>& board, int temp[2], int type, int delta) {
	bool ok = true;
	for (int j = 0; j < 3; j++) {
		int a = temp[0] + coverType[type][j][0];
		int b = temp[1] + coverType[type][j][1];

		if (a < 0 || a >= board.size() || b < 0 || b >= board[0].size()) {
			ok = false;
		}
		// �̹� �ִ°��� ���� ���
		else if ((board[a][b] += delta) > 1) {
			ok = false;
		}
	}
	return ok;
}

// ����Լ��� ����
int solve(vector<vector<int>> board, int whiteN) {
	if (whiteN == 0) return 1;

	if (whiteN % 3 != 0) return 0;

	int ret = 0;
	// ù��° ã��
	int temp[2];
	for (int i = 0; i < board.size(); i++) {
		bool is_break = false;
		for (int j = 0; j < board[0].size(); j++) {
			if (board[i][j]==0) {
				temp[0] = i;
				temp[1] = j;
				is_break = true;
				break;
			}
		}
		if (is_break) break;
	}

	// 4���� ����� ��
	for (int i = 0; i < 4; i++) {
		// ok�̸� ���ȣ��
		if (set(board, temp, i, 1)) {
			ret += solve(board, whiteN - 3);
		}
		// �����·� �����
		set(board, temp, i, -1);
	}
	return ret;
}

int main() {
	int testN;

	cin >> testN;

	for (int testCase = 1; testCase <= testN; testCase++) {
		int h, w;
		cin >> h >> w;
		
		vector<vector<int>> board(h,vector<int>(w));

		int whiteN = 0;

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				char temp;
				cin >> temp;
				// ��������� 0
				if (temp == '.') {
					board[i][j] = 0;
					whiteN++;
				}
				else {
					board[i][j] = 1;
				}
			}
		}

		cout << solve(board, whiteN) << "\n";
	}
}