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

bool isInVector(int value, vector<int> row) {
	for (int i = 0; i < row.size(); i++) {
		if (row[i] == value) {
			return true;
		}
	}
	return false;
}

vector<int> getCol(vector<vector<int> > board, int colNum) {
	vector<int> output;
	for (int row = 0; row < board.size(); row++) {
		output.push_back(board[row][colNum]);
	}
	return output;
}

/*
   block1|block2|block3
   ------|------|------
   --------------------
   block4|block5|block6
   --------------------
   ------|------|------
   block7|block8|block9
*/

vector<int> getBlock(vector<vector<int> > board, int blockNum) {
	int rowStart, rowStop, colStart, colStop;
	switch (blockNum) {
		case 1:
			rowStart = 0;
			rowStop = 3;
			colStart = 0;
			colStop = 3;
			break;
		case 2:
			rowStart = 0;
			rowStop = 3;
			colStart = 3;
			colStop = 6;
			break;
		case 3:
			rowStart = 0;
			rowStop = 3;
			colStart = 6;
			colStop = 9;
			break;
		case 4:
			rowStart = 3;
			rowStop = 6;
			colStart = 0;
			colStop = 3;
			break;
		case 5:
			rowStart = 3;
			rowStop = 6;
			colStart = 3;
			colStop = 6;
			break;
		case 6:
			rowStart = 3;
			rowStop = 6;
			colStart = 6;
			colStop = 9;
			break;
		case 7:
			rowStart = 6;
			rowStop = 9;
			colStart = 0;
			colStop = 3;
			break;
		case 8:
			rowStart = 6;
			rowStop = 9;
			colStart = 3;
			colStop = 6;
			break;
		case 9:
			rowStart = 6;
			rowStop = 9;
			colStart = 6;
			colStop = 9;
			break;
	}
	vector<int> output;
	for(int row = rowStart; row < rowStop; row++) {
		for (int col = colStart; col < colStop; col++) {
			output.push_back(board[row][col]);
		}
	}
	return output;
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

bool checkBlocks(vector<vector<int> > board) {
	vector<int> block;
	vector<int> tmp;
	for (int i = 0; i < board.size(); i++) {
		tmp.push_back(-1);
	}
	for (int blockNum = 1; blockNum <= 9; blockNum++) {
		//get block
		block = getBlock(board, blockNum);
		//reinitialize tmp
		for (int i = 0; i < board.size()+1; i++) {
			tmp[i] = 0;
		}
		//check to see if block is valid
		for (int i = 0; i < block.size(); i++) {
			int val = block[i];
			if (val == 0) {
				continue;
			}
			if (tmp[val-1] == 1) {
				return false;
			}
			else {
				tmp[val-1] = 1;
			}
		}
	}
	return true;
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

	//check squares
	if (! checkBlocks(board)) {
		return false;
	}
        return true;
}

bool solveSudoku(vector<vector<int> > board) {
	vector<int> next = getNextAvailable(board);
	if (next[0] == -1 && next[1] == -1) {
		numBaseCases++;
		if (numBaseCases % 100 == 0) {
			cout << numBaseCases << endl;
			display(board);
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
		//check to see if value is already present in row || column
		if (isInVector(i, board[next[0]]) || isInVector(i, getCol(board, next[1]))) {
			continue;
		
		}
		board[next[0]][next[1]] = i;
		if (! checkBlocks(board)) {
			continue;
		}
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
	/*vector<int> output;
	for (int i = 1; i < 10; i++) {
		output = getBlock(board, i);
		cout << "block: " << i << endl;
		for (int j = 0; j < output.size(); j++) {
			cout << output[j] << ' ';
		}
		cout << endl;
	}
	return;*/
	cout << "solving...\n";
	if (! solveSudoku(board)) {
		cout << "No possible solution.\n";
	}
	cout << "base cases: " << numBaseCases << endl;
}

int main() {
	run();
	/*vector<vector<int> > board  = {
		{2, 0, 0},
		{3, 2, 1},
		{0, 3, 2}};
		int row = 2;
		int col = 0;
		for (int i = 1; i <= 3; i++) {
			cout << "i: " << i << endl;
			if (isInVector(i, board[row])) {
				cout << "\tvalue in row\n";
			}
			if (isInVector(i, getCol(board, col))) {
				cout << "\tvalue in column\n";		
			}
		}*/
		
	return 0;
}
