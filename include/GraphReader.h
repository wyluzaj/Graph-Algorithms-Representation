#ifndef AIZO_GRAFS_GRAPHREADER_H
#define AIZO_GRAFS_GRAPHREADER_H

#include "AdjacencyList.h"
#include "IncidenceMatrix.h"

//adapter class that go through matrix or list
class GraphReader {
public:

    GraphReader(const AdjacencyList &list);


    GraphReader(const IncidenceMatrix &mat);

    //return number of vertices
    int numVertices() const;

    //returns number of neighbors for given vertex
    int numNeighbors(int u) const;

    //i-th neighbor of vertex
    void getNeighbor(int u, int idx, int &v, int &w) const;

private:
    const AdjacencyList *listG;
    const IncidenceMatrix *matG;
};

#endif //AIZO_GRAFS_GRAPHREADER_H
