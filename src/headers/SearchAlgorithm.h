/*
 * SearchAlgorithm.h
 */

#ifndef SEARCHALGORITHM_H
#define SEARCHALGORITHM_H

#define NODE pair<int,Configuration>

#include "Configuration.h"
#include "PQComparator.h"
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
    
    SearchAlgorithm(int searchType, const Configuration& startConfig, const Configuration& goalConfig, int depthLimit=-1);
    
    /* queuing functions */
    void enqueue(const Configuration& c);
    void enqueueAll(const vector<Configuration>& cList);

    // general search algorithm
    void search();
    
private:
    priority_queue<NODE, vector<NODE>, PQComparator> q;
    int searchType;
    Configuration startConfig;
    Configuration goalConfig;
    int depthLimit;
};

#endif
