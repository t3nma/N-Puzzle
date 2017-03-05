/*
 * SearchAlgorithm.h
 */

#ifndef SEARCHALGORITHM_H
#define SEARCHALGORITHM_H

#define NODE pair<int,Configuration*>

#include "Configuration.h"
#include "HeapComparator.h"
#include <unordered_map>
#include <queue>
#include <ctime>


using namespace std;

class SearchAlgorithm
{
public:

    enum SearchType
    {
	ASTAR,
	GREEDY,
	DFS,
	BFS,
	IDFS
    };
    
    SearchAlgorithm(const Configuration& startConfig, const Configuration& goalConfig, int searchType);
    ~SearchAlgorithm();
    
    /* queuing functions */
    bool enqueue(Configuration *c);
    void enqueueAll(vector<Configuration*> cList);

    // general search algorithm
    bool search();
    void iterativeSearch();
    
private:

    priority_queue<NODE, vector<NODE>, HeapComparator> q; // our openSet representation
    unordered_map<string,Configuration*> closedSet;
    
    Configuration *startConfig;
    Configuration *goalConfig;
    int searchType;
    int depthLimit;

    void printPath(Configuration *configPtr);
    void printSolution(Configuration *solution, struct timespec *start, struct timespec *finish);
};

#endif
