/*
 * NPuzzle.cpp
 */

#include "headers/NPuzzle.h"
#include "headers/SearchAlgorithm.h"
using namespace std;

// constructor
NPuzzle::NPuzzle(int N)
{
    this->N = N;
    init();
}

// deconstructor
NPuzzle::~NPuzzle()
{
    delete startConfig;
    delete goalConfig;
}

// A* search implementation
void NPuzzle::Astar() const
{
    SearchAlgorithm astar(SearchAlgorithm.ASTAR);
    astar.search();
}

// Greedy search implementation
void NPuzzle::greedy() const
{
    return;
}

void NPuzzle::IDFS() const
{
    /*
    SearchAlgorithm idfs(SearchAlgorithm.IDFS);
    for(int i=0; i<?; ++i)
	{
	    idfs.setDepthLimit(i);
	    idfs.search();
	}
    */
}

// check if its possible to solve the puzzle
// with its current configurations
bool NPuzzle::isSolvable() const
{
    return startConfig->isSolvable(*goalConfig);
}

// initialize the puzzle configurations
void NPuzzle::init()
{
    Board s(N);
    cout << "Insert the start configuration: (" << N << "x" << N << ")" << endl;
    cin >> s;

    Board e(N);
    cout << "\nInsert the end configuration: (" << N << "x" << N << ")" << endl;
    cin >> e;

    startConfig = new Configuration(s);
    goalConfig = new Configuration(e);
}
