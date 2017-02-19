/*
 * Configuration.cpp
 */

#include "headers/Configuration.h"
using namespace std;

// constructor
Configuration::Configuration(const Board& state, Configuration *parent, int depth)
    : state(state), depth(depth)
{
    this->parent = parent;

    cout << "FDS: " << this->state << endl;
}

// destructor
Configuration::~Configuration()
{
    delete parent;
}

vector<Configuration> Configuration::makeDescendants()
{
    vector<Configuration> descendants;
    vector<Board> stateDescendants = state.makeDescendants();

    vector<Board>::iterator it = stateDescendants.begin();
    for(; it!=stateDescendants.end(); ++it)
    {
	/* TODO FIX
         *
	Configuration newConfig(*it, (this), depth+1);
        descendants.push_back( newConfig );
	 */
    }
    
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
    os << "State: \n" << c.state << endl;
    
    return os;
}
