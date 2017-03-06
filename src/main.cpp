#include "headers/NPuzzle.h"
#include <iostream>
#include <sstream>
#include <vector>

inline void printMenu()
{
    cout << endl << "0-Exit | 1-Astar | 2-Greedy | 3-DFS | 4-BFS | 5-IDFS" << endl;
}

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
	
    NPuzzle *p = new NPuzzle(N);
    while(!p->isSolvable())
    {
	cout << endl << "This instance of the problem is not solvable!" << endl << endl;
	delete p;
	p = new NPuzzle(N);
    }
    
    string inputStr;
    int inputInt;
    
    do
    {
	printMenu();
	cin >> inputStr;

	istringstream ss(inputStr);
	if( !(ss >> inputInt) || inputInt < 0 || inputInt > 5 )
	{
	    cout << endl << "Invalid option! Type again" << endl << endl;
	    continue;
	}

	switch(inputInt)
	{
	    case 1: p->searchAstar(); break;
	    case 2: p->searchGreedy(); break;
	    case 3: p->searchDFS(); break;
	    case 4: p->searchBFS(); break;
	    case 5: p->searchIDFS(); break;
	}
	
    } while(inputInt != 0);

    cout << "Goodbye :)" << endl;
    
    return 0;
}
