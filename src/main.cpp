#include "headers/NPuzzle.h"
#include <iostream>
#include <vector>

int main()
{
    NPuzzle p(3);

    if(p.isSolvable())
	cout << "IS SOLVABLE :)\n";
    else
	cout << "IS NOT SOLVABLE :(\n";
    
    return 0;
}
