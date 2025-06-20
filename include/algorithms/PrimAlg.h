#ifndef AIZO_GRAFS_PRIMALG_H
#define AIZO_GRAFS_PRIMALG_H

#include "../graph/GraphReader.h"
#include "../utils/MinHeap.h"

//Prim (MST)
class PrimAlgorithm {
public:

    PrimAlgorithm(const GraphReader &adapter);


    //stores parents of each vertex in the MST
    //returns total cost of the MST, or -1 if MST not possible
    int compute(int parent[]);

private:
    const GraphReader *graphPtr; //pointer to structure
};

#endif //AIZO_GRAFS_PRIMALG_H
