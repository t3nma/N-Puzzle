/*
 * Configuration.cpp
 */

#include "headers/Board.h"
#include <cstdlib>
#include <iomanip>

using namespace std;


// allowed movements for the blank board piece
//                            D  U   L  R
const int Board::MOVES_X[] = {1, 0, -1, 0};
const int Board::MOVES_Y[] = {0, 1, 0, -1};

// 1-param constructor
Board::Board(int size, int move)
    : arr(new int*[size]), size(size), blankX(-1), blankY(-1), move(move)
{
    for(int i=0; i<size; ++i)
	arr[i] = new int[size];
}

// copy constructor
Board::Board(const Board& b)
    : arr(new int*[b.size]), size(b.size), blankX(b.blankX), blankY(b.blankY), move(b.move)
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
    move = b.move;
    
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

int Board::getMove() const
{
    return move;
}

// blankX setter
void Board::setBlankX(int blankX)
{
    this->blankX = blankX;
}

// move setter
void Board::setMove(int move)
{
  this->move = move;
}

// blankY setter
void Board::setBlankY(int blankY)
{
    this->blankY = blankY;
}

// return board descendants which are
// consequence of the blank piece allowed movements
vector<Board> Board::makeDescendants()
{
    vector<Board> descendants;

    int ignore = -1;
    switch(move)
    {
        case 0: ignore = 2; break;
        case 1: ignore = 3; break;
        case 2: ignore = 0; break;
        case 3: ignore = 1; break;
    }
    
    for(int m=0; m<4; m++)
    {
	if(m != ignore)
	{
	    Board newBoard = (*this);
	    int newBlankX = blankX+MOVES_X[m];
	    int newBlankY = blankY+MOVES_Y[m];
	
	    if( isIn(newBlankX,newBlankY) )
	    {    
		int **b = newBoard.getArr();
		b[blankX][blankY] = arr[newBlankX][newBlankY];
		b[newBlankX][newBlankY] = arr[blankX][blankY];
		
		newBoard.setBlankX(newBlankX);
		newBoard.setBlankY(newBlankY);
                newBoard.setMove(m);
		
		descendants.push_back(newBoard);
	    }
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
// from the start state or false otherwise.
bool Board::isSolvable(const Board& goal) const
{
    int invS = 0, invG = 0;

    for (int i=0; i<size*size; i++)
	for (int j=i+1; j<size*size; j++)
	{
	    if(arr[j/size][j%size] != 0 && arr[i/size][i%size] > arr[j/size][j%size])
		invS++;
	    if(goal.arr[j/size][j%size] != 0 && goal.arr[i/size][i%size] > goal.arr[j/size][j%size])
		invG++;
	}
    
    bool lhs = (!IS_EVEN(size) && IS_EVEN(invS)) || ( IS_EVEN(size) && ( !IS_EVEN((size-blankX)) == IS_EVEN(invS) ) );
    bool rhs = (!IS_EVEN(size) && IS_EVEN(invG)) || ( IS_EVEN(size) && ( !IS_EVEN((size-goal.blankX)) == IS_EVEN(invG) ) );
    
    return lhs == rhs;
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
