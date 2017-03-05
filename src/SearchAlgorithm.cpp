/* 
 * SearchAlgorithm.cpp
 */

#include "headers/SearchAlgorithm.h"
#include <iomanip>
#include <utility>
#include <cstdio>


// constructor
SearchAlgorithm::SearchAlgorithm(const Configuration& startConfig, const Configuration& goalConfig, int searchType)
    : startConfig( new Configuration(startConfig) ),
      goalConfig( new Configuration(goalConfig) ),
      searchType(searchType)
{ }

// destructor
SearchAlgorithm::~SearchAlgorithm()
{
    delete startConfig;
    delete goalConfig;
}

bool SearchAlgorithm::enqueue(Configuration *c)
{   
    int cost = 0;
    
    switch(searchType)
    {
        case ASTAR:
	    cost = c->cost(false,goalConfig); break;
        case GREEDY:
	    cost = c->cost(true,goalConfig); break;
        case DFS:
	    cost = -1*c->getDepth(); break;
        case BFS:
	    cost = c->getDepth();
	    break;
        case IDFS:
	    if(c->getDepth() > depthLimit)
		return false; // ignore sucessor, don't enqueue
	    cost = -1*c->getDepth(); break;
        default:
	    return false;
    }

    unordered_map<string,Configuration*>::const_iterator it = closedSet.find(c->toString());
    
    if(it != closedSet.end())
    {
	if( it->second->getDepth() > c->getDepth() )
        {
	    delete it->second;
	    closedSet[it->first] = c;
	}
	else
	    return false; // ignore sucessor, don't enqueue
    }
    else
	closedSet.insert( make_pair(c->toString(),c) );
    
    q.push( make_pair(cost,c) );
    nodeCount++;
    
    return true; // enqueued
}

void SearchAlgorithm::enqueueAll(vector<Configuration*> cList)
{
    for(size_t i=0; i<cList.size(); i++)
	if(!enqueue(cList[i]))
	    delete cList[i];
}

bool SearchAlgorithm::search()
{
    // init time counter
    struct timespec start, finish;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // enqueue first node and init node counter
    enqueue(startConfig);
    closedSet.insert( make_pair(startConfig->toString(), startConfig) );
    nodeCount = 1;

    // do search step while there are nodes to visit
    while(!q.empty())
    {
	NODE node = q.top(); q.pop();

	if(*node.second == *goalConfig)
	{
	    clock_gettime(CLOCK_MONOTONIC, &finish);
            printSolution(node.second, &start, &finish);
	    
	    return true;
	}
	
	enqueueAll(node.second->makeDescendants());
    }

    return false; // solution not found
}

bool SearchAlgorithm::iterativeSearch()
{   
    depthLimit=0;
    while(!search() && depthLimit <= 150) // TODO handle hard coded limit 
    {
	depthLimit++;
	closedSet.clear();
    }

    return (depthLimit <= 150);
}

void SearchAlgorithm::printPath(Configuration *configPtr)
{
    #ifdef DEBUG
    Configuration *currConfig = configPtr;
    while (currConfig != NULL)
    {
        getchar();
        cout << currConfig->getMove() << endl;
        cout << currConfig << endl;
        currConfig = currConfig->getParent();
    }
    #endif
    
    if (configPtr->parent != NULL)
    {
        printPath(configPtr->parent);
        cout << configPtr->getMove() << " ";
    }
    
    return;
}

void SearchAlgorithm::printSolution(Configuration *solution, struct timespec *start, struct timespec *finish)
{
    // time calculation
    double elapsed = (finish->tv_sec - start->tv_sec) + ((finish->tv_nsec - start->tv_nsec)/1000000000.0);
    
    cout << "Found solution:" << endl;
    //printPath(solution);
    cout << "Depth: " << solution->getDepth() << endl;
    cout << "Nodes: " << nodeCount << endl;
    cout << "Space: " << nodeCount * ((double)sizeof(Configuration) / (1024*1024)) << "mb" << endl;
    cout << setprecision(2) << "Time: " << elapsed << " seconds" << endl;
}
