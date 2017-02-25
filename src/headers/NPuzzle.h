/*
 * NPuzzle.h
 *
 * NPuzzle model its definition, member-functions
 * implemented in NPuzzle.cpp
 */

#ifndef NPUZZLE_H
#define NPUZZLE_H

#include "AstarSearch.h"
#include "Configuration.h"
using namespace std;

class NPuzzle
{
public:
    NPuzzle(int N=4);
    ~NPuzzle();

    /* search methods */
    void Astar() const;
    void greedy() const;

    /* util */
    bool isSolvable() const;
    
private:
    int N;
    Configuration *startConfig;
    Configuration *goalConfig;

    void init();
};

#endif
