/*
 * PQComparator.h
 */

#ifndef HEAPCOMPARATOR_H
#define HEAPCOMPARATOR_H

struct HeapComparator
{
public:
    bool operator()(const NODE& lhs, const NODE& rhs)
    {
        return lhs.first >= rhs.first;
    }
};

#endif
