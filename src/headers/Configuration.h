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
    Configuration(const Board& state, Configuration *parent=NULL, int depth=0);
    ~Configuration();

    /* util */
    vector<Configuration> makeDescendants();
    bool isSolvable(const Configuration& goal) const;
    int cost(bool greedy, const Configuration& goal) const;

    /* operator overloading */
    friend ostream& operator<<(ostream& os, const Configuration& c);
    
private:
    Configuration *parent;
    Board state;
    int depth;
};

#endif
