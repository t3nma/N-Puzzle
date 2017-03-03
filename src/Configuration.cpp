/*
 * Configuration.cpp
 */

#include "headers/Configuration.h"
using namespace std;

// all-member constructor
Configuration::Configuration(const Board& state, int depth, Configuration *parent)
    : state(state),
      depth(depth),
      parent(parent)
{ }

// copy constructor
Configuration::Configuration(const Configuration& c)
    : state(c.state),
      depth(c.depth),
      parent(c.parent)
{ }

// = operation support
Configuration& Configuration::operator=(const Configuration& c)
{
    state = c.state;
    depth = c.depth;

    Configuration *newptr = c.parent;
    delete parent;
    parent = newptr;

    return *this;
}

vector<Configuration*> Configuration::makeDescendants()
{
    vector<Configuration*> descendants;
    vector<Board> stateDescendants = state.makeDescendants();

    for(vector<Board>::iterator it = stateDescendants.begin(); it!=stateDescendants.end(); ++it)
    {
	Configuration *c = new Configuration(*it, depth+1, this);
	descendants.push_back( c );
    }
    
    return descendants;	    
}

bool Configuration::isSolvable(const Configuration *goal) const
{
    return state.isSolvable(goal->state);
}

int Configuration::cost(bool greedy, const Configuration *goal) const
{
    int dx = state.manhattanDist(goal->state);
    return greedy ? dx : depth + dx;
}

int Configuration::getDepth() const
{
    return depth;
}

Configuration *Configuration::getParent() const
{
    return parent;
}

int Configuration::getMove() const
{
    return state.getMove();
}

ostream& operator<<(ostream& os, const Configuration& c)
{
    os << "------- Configuration -------\n\n";
    os << "Depth: " << c.depth << endl << endl;
    os << "State: \n" << c.state << endl << endl;
    
    return os;
}

bool Configuration::operator==(const Configuration& c)
{
    return state.manhattanDist(c.state) == 0;
}
