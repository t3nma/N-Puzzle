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
      searchType(searchType),
      nodeCount(1)
{ }

// destructor
SearchAlgorithm::~SearchAlgorithm()
{
    delete startConfig;   
    delete goalConfig;
}

// enqueue configuration on the priority queue
// based on the search strategy being applied
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
		return false; // ignore sucessor, don't enqueued
	    
	    cost = -1*c->getDepth(); break;
        default:
	    return false;
    }

    // carefully check for repeated configurations
    // without losing the optimal solution
    unordered_map<string,int>::const_iterator it = hash.find(c->toString());
    if(it != hash.end())
    {	
	if(it->second > c->getDepth() )
	    hash[it->first] = c->getDepth();
	else
	    return false; // ignore sucessor, don't enqueue 
    }
    else
	hash.insert( make_pair(c->toString(), c->getDepth()) );
    
    q.push( make_pair(cost,c) );
    nodeCount++;
    
    return true; // enqueued
}

void SearchAlgorithm::enqueueAll(vector<Configuration*> cList)
{
    for(size_t i=0; i<cList.size(); i++)
	enqueue(cList[i]);
}

// our general search function
bool SearchAlgorithm::search()
{
    bool searchResult = false;
    
    // init time counter here unless we're
    // performing IDFS (initialized in iterativeSearch())
    if(searchType != IDFS)
	clock_gettime(CLOCK_MONOTONIC, &start);
    
    // enqueue first node
    enqueue(startConfig);
    hash.insert( make_pair(startConfig->toString(),0) );

    // do search step while there are nodes to visit
    while(!q.empty())
    {
	NODE node = q.top(); q.pop();
	
	if(*node.second == *goalConfig)
	{
	    // get final time
	    struct timespec finish; 
	    clock_gettime(CLOCK_MONOTONIC, &finish);
	    
            printSolution(node.second, &finish);

	    searchResult = true;
	    break;
	}
	
 	enqueueAll(node.second->makeDescendants());
	closedSet.push_back(node.second);	
     }

    clean();
    return searchResult; // solution not found
}

// search function for IDFS, the
// general search function is still called here
bool SearchAlgorithm::iterativeSearch()
{
    // init time counter
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    depthLimit=0;
    while(!search() && depthLimit <= 150) // TODO handle hard coded limit 
    {
	depthLimit++;
	hash.clear();
    }

    return (depthLimit <= 150);
}

void SearchAlgorithm::printPath(Configuration *configPtr)
{
    if (configPtr->getParent() != NULL)
    {
        printPath(configPtr->getParent());
        cout << (char)configPtr->getMove();
    }
}

void SearchAlgorithm::printSolution(Configuration *solution, struct timespec *finish)
{
    // search clock time calculation
    double elapsedTime = (finish->tv_sec - start.tv_sec) + ((finish->tv_nsec - start.tv_nsec)/1000000000.0);
    
    cout << "Found solution:" << endl;
    cout << "Depth: " << solution->getDepth() << endl;
    cout << "Path: "; printPath(solution); cout << endl;
    cout << "Nodes: " << nodeCount << endl;
    cout << "Space: " << nodeCount * ((double)sizeof(Configuration) / (1024*1024)) << "Mb" << endl;
    cout << setprecision(2) << "Time: " << elapsedTime << "s" << endl;
}

void SearchAlgorithm::clean()
{    
    while(!q.empty())
	q.pop();

    if (closedSet.size() > 1)
	closedSet.erase(closedSet.begin()+1, closedSet.end());
}
