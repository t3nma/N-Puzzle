#ifndef NPUZZLE_H
#define NPUZZLE_H

using namespace std;

class NPuzzle
{
public:
    NPuzzle(int N);
    ~NPuzzle();

    /* util */
    void init();
    bool isSolvable() const;

    /* search methods */
    void Astar() const;
    void greedy() const;
    
private:
    int N;
    Configuration *original;
    Configuration *goal;
};

#endif
