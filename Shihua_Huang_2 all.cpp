// Soduku Solver using Brute-Force Search implemted using 
// recursion.

#include <iostream>
#include "Shihua_Huang_2 all.h"

int main(int argc, char * const argv[])
{
	Sudoku x;
	x.solutions = 0;
	x.read_puzzle(argc, argv);
	x.print_puzzle();
	//x.Solve(0, 0);
	x.alternate_Solve(0, 0);
	//x.print_puzzle();

	return 0;
}