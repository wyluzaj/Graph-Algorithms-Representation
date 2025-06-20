#ifndef AIZO_GRAFS_CHECKGRAPH_H
#define AIZO_GRAFS_CHECKGRAPH_H

#include "AdjacencyList.h"
#include "IncidenceMatrix.h"

//verify file vs what we have
class CheckGraph {
public:
   //list
    static bool verify(const AdjacencyList &list, int expectedM);

    //matrix
    static bool verify(const IncidenceMatrix &mat, int expectedM);
};

#endif // AIZO_GRAFS_CHECKGRAPH_H

