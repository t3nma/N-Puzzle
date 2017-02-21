/*
 * NPuzzle.cpp
 */

#include "headers/NPuzzle.h"
#include "headers/Configuration.h"
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
    cout << *startConfig << endl;
    cout << *goalConfig << endl;
}

// Greedy search implementation
void NPuzzle::greedy() const
{
    // TODO
    return;
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
