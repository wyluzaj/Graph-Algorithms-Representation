#ifndef AIZO_GRAFS_BELLMANFORDALG_H
#define AIZO_GRAFS_BELLMANFORDALG_H

#include "GraphReader.h"


//class for shortest path using Bellman-Ford algorithm without - cykles
class BellmanFordAlg {
public:
    BellmanFordAlg(const GraphReader &reader);
    bool compute(int src, int dist[], int parent[]);

private:
    const GraphReader *graph;
};

#endif //AIZO_GRAFS_BELLMANFORDALG_H




