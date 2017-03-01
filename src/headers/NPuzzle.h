/*
 * NPuzzle.h
 *
 * NPuzzle model its definition, member-functions
 * implemented in NPuzzle.cpp
 */

#ifndef NPUZZLE_H
#define NPUZZLE_H

#include "Configuration.h"
using namespace std;

class NPuzzle
{
public:
    NPuzzle(int N=4);
    ~NPuzzle();

    /* search methods */
    void searchAstar() const;
    void searchGreedy() const;
    void searchDFS() const;
    void searchBFS() const;
    void searchIDFS() const;
    
    /* util */
    bool isSolvable() const;
    
private:
    int N;
    Configuration *startConfig;
    Configuration *goalConfig;

    void init();
};

#endif
