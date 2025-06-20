#ifndef AIZO_GRAFS_DIJKSTRAALG_H
#define AIZO_GRAFS_DIJKSTRAALG_H

#include "../graph/GraphReader.h"
#include "../utils/MinHeap.h"

//Dijkstra's algorithm using a MinHeap
class DijkstraAlg {
public:

    DijkstraAlg(const GraphReader &adapter);

    //SP from source node
    void compute(int src, int dist[], int parent[]);

private:
    const GraphReader *graph; //pointer
};

#endif //AIZO_GRAFS_DIJKSTRAALG_H
