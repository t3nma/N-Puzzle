/*
 * Board.h
 *
 * Board model its definition, member-functions
 * implemented in Board.cpp
 */

#ifndef BOARD_H
#define BOARD_H

#include <vector>
using namespace std;

class Board
{
public:
    Board(int *board, int size);
    
    /* util */
    vector<Board> makeDescendants() const;
    int manhatanDist(const Board& goal) const;
    bool isSolvable(const Board& goal) const;
    void printBoard() const;
    
private:
    int *board;
    int size;
    int blank;
};

#endif
