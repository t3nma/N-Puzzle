/*
 * NPuzzle.cpp
 */

#include "Configuration.h"

// constructor
NPuzzle::NPuzzle(int N=4)
{
    this->N = 4;
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
    // TODO
    return true;
}

// initialize the puzzle configurations
void NPuzzle::init() const
{
    // todo
    return;
}
