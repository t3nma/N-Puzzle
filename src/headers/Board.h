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
#include <string>

using namespace std;


class Board
{
public:

    static const int MOVES_X[];
    static const int MOVES_Y[];

    Board(int size, int move=-1);
    Board(const Board& b);
    Board& operator=(const Board& b);
    ~Board();

    /* getters */
    int **getArr() const;
    int getMove() const;
    
    /* setters */
    void setBlankX(int blankX);
    void setBlankY(int blankY);
    void setMove(int move);
    
    /* util */
    vector<Board> makeDescendants();
    int manhattanDist(const Board& goal) const;
    bool isSolvable(const Board& goal) const;
    string toString() const;
    
    /* operator overloading */
    friend istream& operator>>(istream& is, Board& b);
    friend ostream& operator<<(ostream& os, const Board& b);
    
private:
    int **arr;
    int size;
    int blankX;
    int blankY;
    int move;
    
    bool isIn(int x, int y) const;
};

#endif
