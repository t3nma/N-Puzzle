#ifndef NPUZZLE_H
#define NPUZZLE_H

#include "Configuration.h"
using namespace std;

class NPuzzle
{
public:
    NPuzzle(int);
    ~NPuzzle();

    /* search methods */
    void Astar() const;
    void greedy() const;

    /* util */
    bool isSolvable() const;
    
private:
    int N;
    Configuration *original;
    Configuration *goal;

    /* methods */
    void init();
};

#endif
