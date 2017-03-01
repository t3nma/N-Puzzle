/*
 * SearchAlgorithm.h
 */

#ifndef SEARCHALGORITHM_H
#define SEARCHALGORITHM_H

#define NODE pair<int,Configuration>

#include "Configuration.h"
#include "HeapComparator.h"
#include <queue>

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
    
    /* queuing functions */
    void enqueue(const Configuration& c);
    void enqueueAll(const vector<Configuration>& cList);

    // general search algorithm
    bool search();
    void iterativeSearch();
    
private:
    priority_queue<NODE, vector<NODE>, HeapComparator> q;
    Configuration startConfig;
    Configuration goalConfig;
    int searchType;
    int depthLimit;
};

#endif
