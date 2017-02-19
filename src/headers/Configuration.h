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
    Configuration(const Board& state, int depth=0, Configuration* parent=NULL);
    Configuration(const Configuration& c);
    Configuration& operator=(const Configuration& c);
    
    /* util */
    vector<Configuration> makeDescendants();
    bool isSolvable(const Configuration& goal) const;
    int cost(bool greedy, const Configuration& goal) const;

    /* operator overloading */
    friend ostream& operator<<(ostream& os, const Configuration& c);
    
private:
    Board state;
    int depth;
    Configuration *parent;
};

#endif
