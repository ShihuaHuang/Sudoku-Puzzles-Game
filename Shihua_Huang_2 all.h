/*
*  sudoku.h
*  Inspired by: http://web.eecs.utk.edu/courses/spring2012/cs140/Notes/Sudoku/index.html
*/

#ifndef sudoku
#define sudoku

#include <iostream>
#include <vector>
#include <fstream>
using std::vector;
using namespace std;
class Sudoku
{
	// Private
	int puzzle[9][9];
	//private data member: number of solutions

	// Private member function that checks if the named row is valid
	bool row_valid(int row, int col)
	{
		// check if "row" is valid
		for (int j = 0; j < 9; j++)
		{
			if (puzzle[row][j] == puzzle[row][col] && j != col)
				return false;
		}
		return true;
	}

	// Private member function that checks if the named column is valid
	bool col_valid(int row, int col)
	{
		// check validity of "col" 
		for (int i = 0; i < 9; i++)
		{
			if (puzzle[row][col] == puzzle[i][col] && i != row)
				return false;
		}
		return true;
	}

	// Private member function that checks if the named 3x3 block is valid
	bool block_valid(int row, int col)
	{
		// check 3 x 3 block validity 
		for (int i = row / 3 * 3; i < row / 3 * 3 + 3; i++)
		{
			for (int j = col / 3 * 3; j < col / 3 * 3 + 3; j++)
				if (puzzle[i][j] == puzzle[row][col] && row != i&&col != j)
					return false;
		}
		return true;
	}

public:
	// Public member function that reads the incomplete puzzle
	// we are not doing any checks on the input puzzle -- that is,
	// we are assuming they are indeed valid
	int solutions;
	void read_puzzle(int argc, char * const argv[])
	{
		using namespace std;
		// write code that reads the input puzzle using the 
		// guidelines of figure 23 of the bootcamp material
		{
			int value_just_read_from_file;
			vector <int> P; // vector of numbers
			ifstream input_file(argv[1]); // The input file name is what you type in
									   // It contains the numbers P_1 P_2 ...P_M
			if (input_file.is_open())// If file exists in the local directory
			{
				while (input_file >> value_just_read_from_file) // As long as your are not at the "end−of−file"
				{
					P.push_back(value_just_read_from_file);
				}
			}
			else
				cout << "Input_file_does_not_exist_in_PWD" << endl;
			int m = 0;
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					puzzle[i][j] = P[m];
					m++;
				}
			}
		}
	}

	// Public member function that prints the puzzle when called
	void print_puzzle()
	{
		cout << endl;
		std::cout << "Solution #" << solutions + 1 ;
		std::cout << std::endl << "Board Position" << std::endl;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				// check if we have a legitimate integer between 1 and 9
				if ((puzzle[i][j] >= 1) && (puzzle[i][j] <= 9))
				{
					// printing initial value of the puzzle with some formatting
					std::cout << puzzle[i][j] << " ";
				}
				else {
					// printing initial value of the puzzle with some formatting
					std::cout << "X ";
				}
			}
			std::cout << std::endl;
		}
	}

	// Public member function that (recursively) implements the brute-force 
	// search for possible solutions to the incomplete Sudoku puzzle
	bool alternate_Solve(int row, int col)
	{
		int i; int j; int k;
		bool check = true;
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				if (puzzle[i][j] == 0)
					check = false;
			}
		}
		if (check)
		{
			print_puzzle();
			solutions++;
			return true;
		}
		else
		// this part of the code identifies the row and col number of the 
		// first incomplete (i.e. 0) entry in the puzzle.  If the puzzle has
		// no zeros, the variable row will be 9 => the puzzle is done, as 
		// each entry is row-, col- and block-valid...
		// use the pseudo code of figure 3 of the description
		{
			for (i = 0; i < 9; i++)
			{
				for (j = 0; j < 9; j++)
				{
					if (puzzle[i][j] == 0)
					{
						for (k = 1; k <= 9; k++)
						{
							puzzle[i][j] = k;
							if (row_valid(i, j) && col_valid(i, j) && block_valid(i, j))
							{
								int next_row = i; int next_col = j;
								if (j < 8)
									next_col++;
								if (j == 8)
								{
									next_row++;
									next_col = 0;
								}
								if (alternate_Solve(next_row, next_col))
									//puzzle[i][j] = 0
									;
							}
							puzzle[i][j] = 0;
						}
						return false;
					}
				}
			}
			return false;
		}
	}
};

#endif
