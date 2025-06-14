#ifndef AIZO_GRAFS_GRAPHGENERATOR_H
#define AIZO_GRAFS_GRAPHGENERATOR_H
#include "AdjacencyList.h"
#include "IncidenceMatrix.h"
#include <random>

class GraphGenerator {
private:
    std::mt19937 rng;
    std::uniform_int_distribution<int> weightDist; //random weight
    std::uniform_int_distribution<int> vertexDist; //0 - (n-1) randomize vertexes

    void shuffle(int* arr, int size); //shuffle table of ints

public:

    GraphGenerator(int vertexCount);

    void makeAdjacencyList(AdjacencyList& list, int m, bool directed);
    void makeIncidenceMatrix(IncidenceMatrix& matrix, int m, bool directed);
};

#endif //AIZO_GRAFS_GRAPHGENERATOR_H
