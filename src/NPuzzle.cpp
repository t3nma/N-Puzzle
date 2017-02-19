/*
 * NPuzzle.cpp
 */

#include "headers/NPuzzle.h"
#include "headers/Configuration.h"
using namespace std;

// constructor
NPuzzle::NPuzzle(int N=4)
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
    // TODO
    return;
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
  return startConfig.isSolvable(goalConfig);
}

// initialize the puzzle configurations
void NPuzzle::init() const
{
    // todo
    return;
}
