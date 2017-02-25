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

enum SearchType
{
    ASTAR,
    GREEDY,
    DFS,
    BFS,
    IDFS
};

class SearchAlgorithm
{
public:

    SearchAlgorithm(SearchType searchType, const Configuration& startConfig, const Configuration& endConfig);
    
    /* queuing functions */
    void enqueue(const Configuration& c);
    void enqueueAll(const vector<Configuration>& cList);

    // general search algorithm
    void search();

    // setters
    void setDepthLimit(int depthLimit);
    
private:
    priority_queue<NODE, vector<NODE>, PQComparator> q;
    SearchType searchType;
    Configuration startConfig;
    Configuration endConfig;
    int depthLimit;
};

#endif
