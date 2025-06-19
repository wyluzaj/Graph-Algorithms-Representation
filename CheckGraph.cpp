#include "include/CheckGraph.h"


bool CheckGraph::verify(const AdjacencyList &list, int expectedM) {
    int actual = list.used;  //added edges

    if (list.directed) {
        //directed
        return actual == expectedM;
    } else {
        //undirected
        return actual == 2 * expectedM;
    }
}


bool CheckGraph::verify(const IncidenceMatrix &mat, int expectedM) {
    return mat.used == expectedM;
}

