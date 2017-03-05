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
#include <string>

using namespace std;


class Configuration
{
public:
    
    Configuration *parent;
    
    Configuration(const Board& state, int depth=0, Configuration *parent=NULL);
    Configuration(const Configuration& c);
    Configuration& operator=(const Configuration& c);
    
    /* util */
    vector<Configuration*> makeDescendants();
    bool isSolvable(const Configuration* goal) const;
    int cost(bool greedy, const Configuration* goal) const;
    string toString() const;
    
    /* getters */
    int getDepth() const;
    int getMove() const;
    
    /* operator overloading */
    friend ostream& operator<<(ostream& os, const Configuration& c);
    bool operator==(const Configuration& c);

    
private:
    Board state;
    int depth;
};

#endif
