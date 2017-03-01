/* 
 * SearchAlgorithm.cpp
 */

#include "headers/SearchAlgorithm.h"
#include <utility>
#include <cstdio>

// constructor
SearchAlgorithm::SearchAlgorithm(const Configuration& startConfig, const Configuration& goalConfig, int searchType)
    : startConfig(startConfig),
      goalConfig(goalConfig),
      searchType(searchType)
{ }

void SearchAlgorithm::enqueue(const Configuration& c)
{   
    int cost = 0;    
    switch(searchType)
    {
        case ASTAR:
	    cost = c.cost(false,goalConfig); break;
        case GREEDY:
	    cost = c.cost(true,goalConfig); break;
        case DFS:
	    cost = -1*c.getDepth(); break;
        case BFS:
	    cost = c.getDepth(); break;
        case IDFS:
	    if(c.getDepth() > depthLimit)
		return;
	    cost = -1*c.getDepth(); break;
        default:
	    return;
    }

    #ifdef DEBUG
        cout << "enqueing with cost: " << cost << endl;
    #endif

    q.push( make_pair(cost,c) );
}

void SearchAlgorithm::enqueueAll(const vector<Configuration>& cList)
{
    for(size_t i=0; i<cList.size(); i++)
	enqueue(cList[i]);
}

bool SearchAlgorithm::search()
{   
    enqueue(startConfig);
    
    while(!q.empty())
    {
	NODE node = q.top(); q.pop();

	#ifdef DEBUG
	    getchar();
	    cout << "top: (f,d) = (" << node.first << "," << node.second.getDepth() <<  ")" << endl;
	#endif
	
	if(node.second == goalConfig)
	{
	    cout << "Found solution with depth " << node.second.getDepth() << endl;
	    return true;
	}
	
	enqueueAll(node.second.makeDescendants());
    }

    cout << "Solution not found!" << endl;
    return false;
}

void SearchAlgorithm::iterativeSearch()
{   
    depthLimit=0;
    while(!search())
    {
	depthLimit++;
	cout << "searching with limit: " << depthLimit << endl;
    }
}
