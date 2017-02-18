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
    Configuration(Board state, int depth);

    /* util */
    vector<Configuration> makeDescendants() const;
    bool isSolvable(const Configuration& goal) const;
    int cost(bool greedy, const Configuration& goal) const;
    
private:
    Board *state;
    Board *parent;
    int depth;
};

#endif
