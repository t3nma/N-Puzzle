/*
 * NPuzzle.cpp
 */

#include "headers/NPuzzle.h"
#include "headers/SearchAlgorithm.h"

using namespace std;


// constructor
NPuzzle::NPuzzle(int N)
{
    this->N = N;
    init();
}

// deconstructor
NPuzzle::~NPuzzle()
{
    delete startConfig;
    delete goalConfig;
}

// A* search implementation
void NPuzzle::searchAstar() const
{
    SearchAlgorithm astar(*startConfig, *goalConfig, SearchAlgorithm::ASTAR);
    astar.search();
}

// Greedy search implementation
void NPuzzle::searchGreedy() const
{
    SearchAlgorithm greedy(*startConfig, *goalConfig, SearchAlgorithm::GREEDY);
    greedy.search();
}

void NPuzzle::searchDFS() const
{
    SearchAlgorithm dfs(*startConfig, *goalConfig, SearchAlgorithm::DFS);
    dfs.search();
}

void NPuzzle::searchBFS() const
{
    SearchAlgorithm bfs(*startConfig, *goalConfig, SearchAlgorithm::BFS);
    bfs.search();
}

void NPuzzle::searchIDFS() const
{
    SearchAlgorithm idfs(*startConfig, *goalConfig, SearchAlgorithm::IDFS);
    idfs.iterativeSearch();
}

// check if its possible to solve the puzzle
// with its current configurations
bool NPuzzle::isSolvable() const
{
    return startConfig->isSolvable(goalConfig);
}

// initialize the puzzle configurations
void NPuzzle::init()
{
    Board s(N);
    cout << "Insert the start configuration: (" << N << "x" << N << ")" << endl;
    cin >> s;

    Board e(N);
    cout << "\nInsert the end configuration: (" << N << "x" << N << ")" << endl;
    cin >> e;

    startConfig = new Configuration(s);
    goalConfig = new Configuration(e);
}
