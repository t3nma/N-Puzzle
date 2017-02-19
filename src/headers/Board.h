/*
 * Board.h
 *
 * Board model its definition, member-functions
 * implemented in Board.cpp
 */

#ifndef BOARD_H
#define BOARD_H

#define IS_EVEN(N) (N%2 == 0)

#include <vector>
using namespace std;

class Board
{
public:

    static const int MOVES_X[];
    static const int MOVES_Y[];

    Board(int **arr, int size);
    Board(const Board& board);
    ~Board();
    
    /* util */
    vector<Board> makeDescendants() const;
    int manhattanDist(const Board& goal) const;
    bool isSolvable(const Board& goal) const;
    void printBoard() const;
    
private:
    int **arr;
    int size;
    int blank_x, blank_y;
    
    bool isIn(int x, int y) const;
    int invCount(int *bInv, int lo, int hi);
};

#endif
