/*
 * Configuration.h
 *
 * Configuration model its definition, member-functions
 * implemented in Configuration.cpp
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "Board.h"
#include <vector>
using namespace std;

class Configuration
{
public:
    Configuration(Configuration *parent, const Board& state, int depth);
    ~Configuration();
    
    /* util */
    vector<Configuration> makeDescendants() const;
    bool isSolvable(const Configuration& goal) const;
    int cost(bool greedy, const Configuration& goal) const;
    
private:
    Configuration *parent;
    Board *state;
    int depth;
};

#endif
