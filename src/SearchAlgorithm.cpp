/* 
 * SearchAlgorithm.cpp
 */

#include "headers/SearchAlgorithm.h"
#include <iomanip>
#include <utility>
#include <cstdio>

// constructor
SearchAlgorithm::SearchAlgorithm(const Configuration& startConfig, const Configuration& goalConfig, int searchType)
    : startConfig(new Configuration(startConfig)),
      goalConfig(new Configuration(goalConfig)),
      searchType(searchType)
{ }

void SearchAlgorithm::enqueue(Configuration *c)
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
	    cost = c->getDepth(); break;
        case IDFS:
	    if(c->getDepth() > depthLimit)
		return;
	    cost = -1*c->getDepth(); break;
        default:
	    return;
    }

    #ifdef DEBUG
        cout << "enqueing with cost: " << cost << endl;
    #endif

    q.push( make_pair(cost,c) );
}

void SearchAlgorithm::enqueueAll(const vector<Configuration*>& cList)
{
    for(size_t i=0; i<cList.size(); i++)
	enqueue(cList[i]);
}

bool SearchAlgorithm::search()
{
    struct timespec start, finish;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    enqueue(startConfig);

    #ifdef DEBUG
    cout << "Enqued startConfig, size: " << q.size() << endl;
    #endif
    
    while(!q.empty())
    {
	NODE node = q.top(); q.pop();

	#ifdef DEBUG
        getchar();
        cout << "top: (f,d) = (" << node.first << "," << node.second->getDepth() <<  ")" << endl;
	#endif
	 
	if(*node.second == *goalConfig)
	{
	    clock_gettime(CLOCK_MONOTONIC, &finish);
            #ifdef DEBUG
            cout << "Going to print the solution..." << endl;
            #endif 

            printSolution(node.second, &start, &finish);

            while(!q.empty())
	    {
		NODE n = q.top(); q.pop();
		delete n.second;
	    }
	    
	    return true;
	}

	enqueueAll(node.second->makeDescendants());

	#ifdef DEBUG
	cout << "Enqued descendants" << endl;
	#endif

	delete node.second;

	#ifdef DEBUG
	cout << "Node deleted" << endl;
	#endif
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
    
    if (configPtr->getParent() != NULL)
    {
        printPath(configPtr->getParent());
        cout << configPtr->getMove();
    }
    return;
}

void SearchAlgorithm::printSolution(Configuration *solution, struct timespec *start, struct timespec *finish)
{
    #ifdef DEBUG
    cout << "Calculating elapsed time..." << endl;
    #endif

    // time calculation
    double elapsed = (finish->tv_sec - start->tv_sec) + ((finish->tv_nsec - start->tv_nsec)/1000000000.0);
    
    cout << "Found solution: ";
    
    printPath(solution);
    
    cout << setprecision(2) << " at depth " << solution->getDepth() << " in " << elapsed << " seconds" << endl;
}
