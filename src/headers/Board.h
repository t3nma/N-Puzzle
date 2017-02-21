/*
 * Board.h
 *
 * Board model its definition, member-functions
 * implemented in Board.cpp
 */

#ifndef BOARD_H
#define BOARD_H
#define IS_EVEN(N) (N%2 == 0)

#include <iostream>
#include <vector>
using namespace std;

class Board
{
public:

    static const int MOVES_X[];
    static const int MOVES_Y[];

    Board(int size);
    Board(const Board& b);
    Board& operator=(const Board& b);
    ~Board();

    /* getters */
    int **getArr() const;

    /* setters */
    void setBlankX(int blankX);
    void setBlankY(int blankY);
    
    /* util */
    vector<Board> makeDescendants();
    int manhattanDist(const Board& goal) const;
    bool isSolvable(const Board& goal) const;

    /* operator overloading */
    friend istream& operator>>(istream& is, Board& b);
    friend ostream& operator<<(ostream& os, const Board& b);
    
private:
    int **arr;
    int size;
    int blankX;
    int blankY;
    
    bool isIn(int x, int y) const;
    int invCount(int *v, int lo, int hi) const;
    int invCountMerge(int *v, int lo, int mid, int hi) const;
};

#endif
