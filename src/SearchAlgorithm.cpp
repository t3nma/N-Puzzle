/* 
 * SearchAlgorithm.cpp
 */

#include "headers/SearchAlgorithm.h"
#include <utility>

SearchAlgorithm::SearchAlgorithm(SearchType searchType, const Configuration& startConfig, const Configuration& endConfig)
    : searchType(searchType), startConfig(startConfig), endConfig(endConfig), depthLimit(-1)
{
    q = priority_queue< NODE, vector<NODE>, PQComparator >();
}

void SearchAlgorithm::enqueue(const Configuration& c)
{
    switch(searchType)
    {
        case SearchType.ASTAR:
	    q.push( make_pair(c.cost(false,endConfig), c) );
	    break;
        case SearchType.GREEDY:
	    q.push( make_pair(c.cost(true,endConfig), c) );
	    break;
        case SearchType.DFS:
	    q.push( make_pair(1, c) );
	    break;
        case SearchType.BFS:
	    q.push( make_pair(c.getDepth(), c) );
	    break;
        case SearchType.IDFS:
	    if( c.getDepth <= depthLimit )
		q.push( make_pair(1, c) );
	    break;
        default:
	    return;
    }
}

void SearchAlgorithm::enqueueAll(const vector<Configuration>& cList)
{
    for(size_t i=0; i<cList.size(); i++)
	enqueue(cList[i]);
}

void SearchAlgorithm::search()
{
    /*
    q.push(startConfig);

    while(q.empty())
    {
	
    }
    */
    
    return;
}

void SearchAlgorithm::setDepthLimit(int depthLimit)
{
    this->depthLimit = depthLimit;
}
