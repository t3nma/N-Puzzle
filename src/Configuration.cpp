/*
 * Configuration.cpp
 */

#include "headers/Configuration.h"
using namespace std;


// constructor
Configuration::Configuration(Configuration *parent, const Board& state, int depth) : depth(depth)
{
    this->parent = parent;
    this->state = new Board(state);
}

// destructor
Configuration::~Configuration()
{
    delete parent;
    delete state;
}

vector<Configuration> Configuration::makeDescendants() const
{
    vector<Board> stateDescendants = state->getDescendants();
    vector<Board>::iterator it = stateChilds.begin();

    vector<Configuration> descendants;
    for(; it!=stateChilds.end(); ++it)
        descendants.push_back( Configuration(this, *it, depth+1) );

    return descendants;	    
}

bool Configuration::isSolvable(const Configuration& goal) const
{
    return state->isSolvable(*goal.state);
}

int Configuration::cost(bool greedy, const Configuration& goal) const
{
    int dx = state->manhattanDist(*goal.state);
    return greedy ? dx : depth + dx;
}
