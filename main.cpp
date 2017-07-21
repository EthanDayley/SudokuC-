#include <iostream>
#include <vector>
#include <string>

using namespace std;

int numBaseCases = 0;

void display(vector<vector<int> > board) {
	for (int row = 0; row < board.size(); row++) {
		for (int col = 0; col < board[row].size(); col++) {
			cout << board[row][col] << ' ';
		}
		cout << '\n';
	}
}

vector<int> getNextAvailable(vector<vector<int> > board) {
	vector<int> r;
	r.push_back(-1);
	r.push_back(-1);
	for (int row = 0; row < board.size(); row++) {
		for (int col = 0; col < board[row].size(); col++) {
			if (board[row][col] == 0) {
				r[0] = row;
				r[1] = 	col;
				return r;
			}
		}
	}
	return r;
}

bool isValid(vector<vector<int> > board) {
        int * tmp = new int[board.size()];
        //initialize tmp array
        //tmp is a list of zeros.
        //if a number is found in a row the corresponding index of tmp is flipped to a one
        for (int i = 0; i < board.size(); i++) {
                tmp[i] = 0;
        }
        //check rows
        //iterate through rows
        for (int row = 0; row < board.size(); row++) {
                for (int i = 0; i < board.size(); i++) {
                        tmp[i] = 0;
                }
                for (int col = 0; col < board.size(); col++) {
                        if (board[row][col] <= board.size() && board[row][col] >= 1) {
                                int val = board[row][col];
                                if (tmp[val-1] == 1) {
                                        //We know that it is not valid
                                        return false;
                                }
                                else {
                                        tmp[val-1] = 1;
                                }
                        }
                        else {
                                //We know that it is not valid
                                return false;
                        }
                }
        }
        for (int i = 0; i < board.size()+1; i++) {
                tmp[i] = 0;
        }
        //check columns
        //iterate through columns
        for (int col = 0; col < board.size(); col++) {
                for (int i = 0; i < board.size()+1; i++) {
                        tmp[i] = 0;
                }
                for (int row = 0; row < board.size(); row++) {
                        if (board[row][col] <= board.size() && board[row][col] >= 1) {
                                int val = board[row][col];
                                if (tmp[val-1] == 1) {
                                        //We know that it is not valid
                                        return false;
                                }
                                else {
                                        tmp[val-1] = 1;
                                }
                        }
                        else {
                                //We know that it is not valid
                                return false;
                        }
                }
        }
        return true;
}

bool solveSudoku(vector<vector<int> > board) {
	vector<int> next = getNextAvailable(board);
	if (next[0] == -1 && next[1] == -1) {
		numBaseCases++;
		if (numBaseCases % 100000 == 0) {
			cout << numBaseCases << endl;
		}
		if (isValid(board)) {
			cout << "Solved: \n";
			display(board);
			return true;
		}
		else {
			return false;
		}
	}
	for (int i = 1; i <= board.size(); i++) {
		board[next[0]][next[1]] = i;
		if (solveSudoku(board)) {
			return true;
		}
	}
	return false;
}

void run() {
	vector<vector<int> > board;/* = {
		{2, 0, 0},
	       	{3, 2, 1},
		{0, 3, 2}};*/
	int width, tmp;
	cout << "Input width: ";
	cin >> width;
	for (int i = 0; i < width; i++) {
		vector<int> newRow;
		board.push_back(newRow);
		for (int j = 0; j < width; j++) {
			cin >> tmp;
			board[i].push_back(tmp);
		}
	}
	cout << "solving...\n";
	if (! solveSudoku(board)) {
		cout << "No possible solution.\n";
	}
	cout << "base cases: " << numBaseCases << endl;
}

int main() {
	run();
	return 0;
}
