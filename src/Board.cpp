/*
 * Configuration.cpp
 */

#include "headers/Board.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

// SIZE = 3
//
//    0 1 2
// 0 |1|2|3|
// 1 |4|5|6|
// 2 |7|8|0|
//
// for merge sort
// i index
// m[i/size][i%size]
//
//  0 1 2 3 4 5 6 7 8
// |1|2|3|4|5|6|7|8|0


// SIZE=2
//
// INICIAL
//    0 1
// 0 |2|1|
// 1 |3|4|
//
// FINAL
//    0 1
// 0 |3|1|
// 1 |4|2|
//
//  0 1 2 3 4
// | |3|1|4|2| = b
// INICIAL[b[i]] = i;
//
// i==1 := INICIAL[b[i]->3]=i
// i==2 := INICIAL[b[i]->1]=i
//
// bINICIAL
//    0 1
// 0 |4|2|
// 1 |1|3|
//
// bFINAL
//    0 1
// 0 |1|2|
// 1 |3|4|

   
const int Board::MOVES_X[] = {+1, 0,-1, 0};
const int Board::MOVES_Y[] = { 0,+1, 0,-1};

Board::Board(int **arr, int size) : size(size)
{
    this->arr = new *int[size];
    for(int i=0; i<size; ++i)
    {
        this->arr[i] = new int[size];
        for(int j=0; j<size; ++j)
        {
            this->arr[i][j] = arr[i][j];
            
            if (this->arr[i][j] == 0)
            {
                this->blank_x = i;
                this->blank_y = j;
            }
        }
    }
}

Board::Board(const Board& board)
{
    this->size = board.size;
    this->blank_x = blank_x;
    this->blank_y = blank_y;
    
    for (int i=0; i<size; i++)
	for (int j=0; j<size; j++)
	    this->arr[i][j] = board.arr[i][j];
}

Board::~Board()
{
    for(int i=0; i<size; ++i)
        delete [] arr[i];
    delete [] arr;
}

vector<Board> Board::makeDescendants()
{
    vector<Board> descendants;
    
    for(int m=0; m<4; m++)
    {
        int newArr[size][size];
        int newBlank_x = blank_x+MOVES_X[m];
        int newBlank_y = blank_y+MOVES_Y[m];

        if( isIn(newBlank_x,newBlank_y) )
        {
            for(int i=0; i<size; i++)
                for(int j=0; j<size; j++)
                    newArr[i][j] = arr[i][j];

            newArr[blank_x][blank_y] = arr[newBlank_x][newBlank_y];
            newArr[newBlank_x][newBlank_y] = arr[blank_x][blank_y];
        }

        descendants.push_back( Board(newArr,size) );
        
    }
    
    return descendants;
}

int Board::manhattanDist(const Board& goal) const
{
    int dist = 0;

    for(int i=0; i<size*size; ++i)
        for(int j=0; j<size*size; ++j)
            if(arr[size/i][size%i] == goal.arr[size/j][size%j])
            {
                dist += abs((size/i)-(size/j)) + abs((size%i)-(size%j));
                break;
            }
    
    return dist;
}

bool Board::isSolvable(const Board& goal) const
{
    int b[(size*size)+1];
    int bInv[(size*size)+1];
    
    for (int i=1; i<(size*size)+1; i++)
        b[i] = goal.arr[i/size][i%size] == 0 ? size*size : goal.arr[i/size][i%size];

    for (int i=1; i<(size*size)+1; i++)
        bInv[b[i]] = i;
    
    int numInv = invCount(bInv, 1, (size*size)+1);

    return ( !IS_EVEN(size) && IS_EVEN(numInv) ) ||
           ( IS_EVEN(size) && ( (IS_EVEN(numInv) && !IS_EVEN(blank_y+1)) || (!IS_EVEN(numInv) && IS_EVEN(blank_y+1)) ) );
}

void Board::printBoard() const
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
            cout << setw(2) << arr[i][j] << " ";
        cout << endl;
    }
}

bool Board::isIn(int x, int y) const
{
    return x >= 0 && x < size && y >= 0 && y < size;
}

int Board::invCount(int *bInv, int lo, int hi) const
{
    /* Counts the number of inversions using mergesort O(log n) */
    int count = 0;
    int mid;
    
    if (lo<hi)
    {
        mid = lo+(hi-lo)/2;
        invCount(bInv, lo, mid);
        invCount(bInv, mid+1, hi);
        count += merge(bInv, lo, mid, high);
    }
    return count;
}

int Board::merge(int *bInv, int lo, int mid, int hi) const
{
    int count, i, p1, p2, aux[end+1];

    p1 = lo;    
    p2 = mid+1; 
    i = lo;
    
    while (p1 <= mid && p2 <= hi)
    {          
        if (v[p1] <= v[p2])
            aux[i++] = v[p1++];
        else
        {
            aux[i++] = v[p2++];
            count += mid-p1+1;
        }
    }
    
    while (p1 <= mid)
            aux[i++] = v[p1++];   
    while (p2 <= hi)
            aux[i++] = v[p2++];
    
    for (i=lo; i<=hi; i++)
            v[i] = aux[i];

    return count;
}


