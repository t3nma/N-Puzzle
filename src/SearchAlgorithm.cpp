/* 
 * SearchAlgorithm.cpp
 */

#include "headers/SearchAlgorithm.h"
#include <utility>

SearchAlgorithm::SearchAlgorithm(int searchType, const Configuration& startConfig, const Configuration& goalConfig, int depthLimit)
    : searchType(searchType), startConfig(startConfig), goalConfig(goalConfig), depthLimit(depthLimit)
{ }

void SearchAlgorithm::enqueue(const Configuration& c)
{
    switch(searchType)
    {
        case ASTAR:
	    q.push( make_pair( c.cost(false,goalConfig),c ) );
	    break;
        case GREEDY:
	    q.push( make_pair( c.cost(true,goalConfig),c ) );
	    break;
        case DFS:
	    q.push( make_pair(0,c) );
	    break;
        case BFS:
	    q.push( make_pair(c.getDepth(),c) );
	    break;
        case IDFS:
	    if( c.getDepth() <= depthLimit )
		q.push( make_pair(0,c) );
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
    enqueue(startConfig);
    
    while(!q.empty())
    {
	NODE nextNode = q.top(); q.pop();

	if(nextNode.second == goalConfig)
	{
	    cout << "Found solution @ depth " << nextNode.second.getDepth() << endl;
	    return;
	}
	
	enqueueAll(nextNode.second.makeDescendants());
    }

    cout << "Solution not found!" << endl;
}
