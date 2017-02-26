/*
 * PQComparator.h
 */

#ifndef PQCOMPARATOR_H
#define PQCOMPARATOR_H

struct PQComparator
{   
    bool operator()(const NODE& lhs, const NODE& rhs)
    {
        return lhs.first >= rhs.first;
    }
};

#endif
