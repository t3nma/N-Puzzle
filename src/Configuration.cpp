/*
 * Configuration.cpp
 */

#include "headers/Configuration.h"
using namespace std;

// constructor
Configuration::Configuration(const Board& state, int depth, Configuration* parent)
    : state(state), depth(depth), parent(parent)
{ }

// copy constructor
Configuration::Configuration(const Configuration& c)
    : state(c.state), depth(c.depth), parent(c.parent)
{ }

// = operation support
Configuration& Configuration::operator=(const Configuration& c)
{
    Configuration *newPtr = c.parent;
    delete parent;
    parent = newPtr;
    
    state = c.state;
    depth = c.depth;

    return *this;
}

vector<Configuration> Configuration::makeDescendants()
{
    vector<Configuration> descendants;
    vector<Board> stateDescendants = state.makeDescendants();

    for(vector<Board>::iterator it = stateDescendants.begin(); it!=stateDescendants.end(); ++it)
	descendants.push_back( Configuration(*it, depth+1, this) );
    
    return descendants;	    
}

bool Configuration::isSolvable(const Configuration& goal) const
{
    return state.isSolvable(goal.state);
}

int Configuration::cost(bool greedy, const Configuration& goal) const
{
    int dx = state.manhattanDist(goal.state);
    return greedy ? dx : depth + dx;
}

ostream& operator<<(ostream& os, const Configuration& c)
{
    os << "------- Configuration -------\n\n";
    os << "Depth: " << c.depth << endl << endl;
    os << "State: \n" << c.state << endl << endl;
    
    return os;
}
