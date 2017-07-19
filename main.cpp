/*
 * This is a program to recursively solve a sudoku puzzle
 * See https://en.wikipedia.org/wiki/Sudoku
 * This is a homework problem for CS1410 
 * reference http://digital.cs.usu.edu/~watson/cs1410/hw8.htm for more info
 * */
#include <iostream>

using namespace std;

const int boardWidth = 3;

bool isValid(int ** board) {
        int * tmp = new int[boardWidth];
        //initialize tmp array
        //tmp is a list of zeros.
        //if a number is found in a row the corresponding index of tmp is flipped to a one
        for (int i = 0; i < boardWidth; i++) {
                tmp[i] = 0;
        }
        //check rows
        //iterate through rows
        for (int row = 0; row < boardWidth; row++) {
                for (int i = 0; i < boardWidth; i++) {
                        tmp[i] = 0;
                }
                for (int col = 0; col < boardWidth; col++) {
                        if (board[row][col] <= boardWidth && board[row][col] >= 1) {
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
        for (int i = 0; i < boardWidth+1; i++) {
                tmp[i] = 0;
        }
        //check columns
        //iterate through columns
        for (int col = 0; col < boardWidth; col++) {
                for (int i = 0; i < boardWidth+1; i++) {
                        tmp[i] = 0;
                }
                for (int row = 0; row < boardWidth; row++) {
                        if (board[row][col] <= boardWidth && board[row][col] >= 1) {
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


void display(int ** input) {
	for (int row = 0; row < boardWidth; row++) {
		for (int col = 0; col < boardWidth; col++) {
			cout << input[row][col] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

//this is a function to get the next available space in a 2D array
// returns a pointer to an array formatted {row, column}
int * getNextAvailable(int ** board) {
	static int r[2];
	for (int row = 0; row < boardWidth; row++) {
		for (int col = 0; col < boardWidth; col++) {
			if (board[row][col] == 0) {
				r[0] = row;
				r[1] = 	col;
				return r;
			}
		}
	}
	r[0] = -1;
	r[1] = -1;
	return r;
}

int ** arrCopy(int ** input) {
	int ** cpy = new int * [boardWidth];
	for (int row = 0; row < boardWidth; row++) {
		cpy[row] = new int[boardWidth];
		for (int col = 0; col < boardWidth; col++) {
			cpy[row][col] = input[row][col];
		}
	}
	return cpy;
}

// This is the main recursive function.
// It takes as input an n*n array,
// the bool isComplete,
bool getSolution(int ** grid) {
	cout << "\n########################\nIn getSolution\n########################\n";
	int * next = new int[2];
	//cout << "&next: " << &next << endl;
	next = getNextAvailable(grid);

	//cout << "next[0]: " << next[0] << endl << "next[1]: " << next[1] << endl;
	//display(grid);
	
	//actual logic and recursion
	if (next[0] == -1 && next[1] == -1) {
		//base case
		//check to see if it is a solution
		cout << "Reached base case\n";
		cout << "&next: " << &next << endl;
		display(grid);
		if (isValid(grid)) {
			//cout << "Valid\n";
			return true;
		}
		else {
			//cout << "Invalid\n";
			return false;
		}
	}
	//check all options
	int ** tmp = new int*[boardWidth];
	tmp = arrCopy(grid);
	cout << "iterating\n";
	for (int i = 1; i <= boardWidth; i++) {
		tmp = arrCopy(grid);
		cout << "curr arr val: " << i << endl;
		//cout << "next[0]: " << next[0] << endl << "next[1]: " << next[1] << endl;
		cout << "&next: " << &next << endl;
		display(tmp);
		tmp[next[0]][next[1]] = i;
		cout << "after arrCopy\n";
		if (getSolution(tmp)) {
			return true;
		}
		else {
			cout << "returned false\n";
		}
		delete tmp;

	}
	delete tmp;
	return false;
}

void run() {
	int boardInit[boardWidth][boardWidth] = {
		{2, 0, 0},
	       	{3, 2, 1},
		{0, 3, 2}};
	int ** board = new int*[boardWidth];
	for (int row = 0; row < boardWidth; row++) {
		board[row] = new int[boardWidth];
		for (int col = 0; col < boardWidth; col++) {
			board[row][col] = boardInit[row][col];
		}
	}
	/*
	 * 2 1 3
	 * 3 2 1
	 * 1 3 2
	 * */
	cout << getSolution(board) << endl;
	//int * available = getNextAvailable(0, 0, board);
	//cout << available[0] << ' ' << available[1] << endl;
}


int main() {
	run();
	/*int boardInit[boardWidth][boardWidth] = {
		{2, 0, 0},
	       	{3, 2, 1},
		{0, 3, 2}};
	int ** board = new int*[boardWidth];
	for (int row = 0; row < boardWidth; row++) {
		board[row] = new int[boardWidth];
		for (int col = 0; col < boardWidth; col++) {
			board[row][col] = boardInit[row][col];
		}
	}
	int ** cpy = new int*[boardWidth];
	cpy = arrCopy(board);
	display(board);
	display(cpy);
	cpy[0][2] = 11;
	display(board);
	display(cpy);*/
	return 0;
}
