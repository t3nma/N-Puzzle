/*
 * Configuration.cpp
 */

#include "headers/Board.h"
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

// allowed movements for the blank board piece
const int Board::MOVES_X[] = {1, 0, -1, 0};
const int Board::MOVES_Y[] = {0, 1, 0, -1};

// 1-param constructor
Board::Board(int size)
    : arr(new int*[size]), size(size), blankX(-1), blankY(-1)
{
    for(int i=0; i<size; ++i)
	arr[i] = new int[size];
}

// copy constructor
Board::Board(const Board& b)
    : arr(new int*[b.size]), size(b.size), blankX(b.blankX), blankY(b.blankY)
{   
    for (int i=0; i<size; i++)
    {
	arr[i] = new int[size];
	for (int j=0; j<size; j++)
	    arr[i][j] = b.arr[i][j];
    }
}

// = operation support
Board& Board::operator=(const Board& b)
{
    int** newArr = new int*[b.size];
    
    for(int i=0; i<b.size; ++i)
    {
	newArr[i] = new int[b.size];

	if(arr[i] != NULL)
	    delete[] arr[i];

	for(int j=0; j<size; ++j)
	    newArr[i][j] = b.arr[i][j];
    }

    delete[] arr;
    
    arr = newArr;
    size = b.size;
    blankX = b.blankX;
    blankY = b.blankY;

    return *this;
}

// destructor
Board::~Board()
{
    for(int i=0; i<size; ++i)
        delete[] arr[i];
    delete[] arr;
}

// arr getter
int** Board::getArr() const
{
    return arr;
}

// return board descendants, which are
// consequence of the blank piece allowed movements
vector<Board> Board::makeDescendants()
{
    vector<Board> descendants;
    
    for(int m=0; m<4; m++)
    {
	Board newBoard = (*this);
        int newBlankX = blankX+MOVES_X[m];
        int newBlankY = blankY+MOVES_Y[m];
	
        if( isIn(newBlankX,newBlankY) )
        {    
	    int **b = newBoard.getArr();
            b[blankX][blankY] = arr[newBlankX][newBlankY];
            b[newBlankX][newBlankY] = arr[blankX][blankY];

	    descendants.push_back(newBoard);
	}
    }
    
    return descendants;
}

// calc and return the manhattanDist
// to the goal Board
int Board::manhattanDist(const Board& goal) const
{
    int dist = 0;

    for(int i=0; i<size*size; ++i)
        for(int j=0; j<size*size; ++j)
            if(arr[i/size][i%size] == goal.arr[j/size][j%size])
            {
                dist += abs((i/size)-(j/size)) + abs((i%size)-(j%size));
                break;
            }
    
    return dist;
}

// Returns true if the goal state is reachable
// from the start state or false otherwise
bool Board::isSolvable(const Board& goal) const
{    
    int b[(size*size)+1];
    int ib[(size*size)+1];
    int bInv[(size*size)+1];
    int numInv = 0;
    for (int i=0; i<size*size; i++)
    {
	b[i+1] = goal.arr[i/size][i%size] == 0 ? size*size : goal.arr[i/size][i%size];
	ib[b[i+1]] = i+1;
    }

    for (int i=1; i<=size*size; i++)
    {
	int valueArr = arr[(i-1)/size][(i-1)%size];
	if (valueArr == 0)
	{
	    bInv[i] = ib[size*size];
	    // Compensation for the number of inversions due to
	    // the blank square represented by size*size
	    numInv -= (size*size)-i;
	}
	else
	    bInv[i] = ib[valueArr];
    }
    
    numInv += invCount(bInv, 1, size*size);

    //    cout << "NUM_INV = " << numInv << endl;
    return ( !IS_EVEN(size) && IS_EVEN(numInv) ) ||
           ( IS_EVEN(size) && ( (IS_EVEN(numInv) && !IS_EVEN(blankX)) || (!IS_EVEN(numInv) && IS_EVEN(blankX)) ) );
}

// >> operator support
// read board and find the blank (x,y) position
istream& operator>>(istream& is, Board& b)
{

    for(int i=0; i<b.size; ++i)
	for(int j=0; j<b.size; ++j)
	{
	    is >> b.arr[i][j];

	    // blank?
	    if(b.arr[i][j] == 0)
	    {
		b.blankX = i;
		b.blankY = j;
	    }
	}

    return is;
}

// << operator support
// outputs the board
ostream& operator<<(ostream& os, const Board& b)
{
    for(int i=0; i<b.size; ++i)
    {
	for(int j=0; j<b.size; ++j)
	    cout << setw(2) << b.arr[i][j] << " ";
	cout << endl;
  }

    return os;
}

// check weather the coordinate (x,y)
// is an allowed position of the board
bool Board::isIn(int x, int y) const
{
    return x >= 0 && x < size && y >= 0 && y < size;
}

// Counts the number of inversions using mergesort O(log n)

int Board::invCount(int *bInv, int lo, int hi) const
{
    int count = 0;
    
    if (lo<hi)
    {
        int mid = lo+(hi-lo)/2;
        count += invCount(bInv, lo, mid);
        count += invCount(bInv, mid+1, hi);
        count += merge(bInv, lo, mid, hi);
    }
    
    return count;
}

// Instead of merging two parts of the list, it counts the
// number of inversions that he would have made by merging
// them and maintaining the resulting list in order
int Board::merge(int *bInv, int lo, int mid, int hi) const
{   
    int count=0, i, p1, p2, aux[hi+1];

    p1 = lo;    
    p2 = mid+1; 
    i = lo;
    
    while (p1 <= mid && p2 <= hi)
    {
        if (bInv[p1] <= bInv[p2])
            aux[i++] = bInv[p1++];
        else
        {
            aux[i++] = bInv[p2++];
	    count += mid-p1+1;
        }
    }
    
    while (p1 <= mid)
	aux[i++] = bInv[p1++];

    while (p2 <= hi)
	aux[i++] = bInv[p2++];
    
    for (i=lo; i<=hi; i++)
	bInv[i] = aux[i];

    return count;
}

