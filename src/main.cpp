#include "headers/NPuzzle.h"
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char *argv[])
{
    int N=4;
    
    if(argc == 1)
	cout << "Puzzle size not provided, assuming size 4..." << endl << endl;
    else
    {
	// validate input
	istringstream ss(argv[1]);
	if( !(ss >> N) || N < 2 )
	{
	    cerr << "Invalid number!\nUsage >> ./a.out {size >= 2}" << endl;
	    return 1;
	}
    }
    
    NPuzzle p(N);
    
    if(p.isSolvable())
	p.searchAstar();
    else
	cout << "This instance of the problem is not solvable." << endl;
    
    return 0;
}
