#ifndef AIZO_GRAFS_INCIDENCEMATRIX_H
#define AIZO_GRAFS_INCIDENCEMATRIX_H

#include <iostream>

class IncidenceMatrix {
public:
    int nV;         //vertexes
    int mE;         //edges
    int used;       // how many edges already added
    bool directed;
    int* matrix;      // matrix


    IncidenceMatrix(int vertices, int edgeCapacity, bool isDirected);


    ~IncidenceMatrix();


    void addEdge(int u, int v, int w);


    void print() const;
};

#endif //AIZO_GRAFS_INCIDENCEMATRIX_H
