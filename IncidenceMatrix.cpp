#include "include/IncidenceMatrix.h"
#include <iostream>
using namespace std;


IncidenceMatrix::IncidenceMatrix(int vertices, int edgeCapacity, bool isDirected) {

    nV = vertices;
    mE = edgeCapacity;
    used = 0;
    directed = isDirected;

    matrix = new int[nV * mE];
    for (int i = 0; i < nV * mE; ++i) {
        matrix[i] = 0;
    }
}

IncidenceMatrix::~IncidenceMatrix() {
    delete[] matrix;
}


void IncidenceMatrix::addEdge(int u, int v, int w) {

    if (used < mE) {
        int col = used;  // number col = index next edge

        // line u, col = w
        matrix[u * mE + col] = w;

        //line v, col = -w directed, w undirected
        if (directed) {
            matrix[v * mE + col] = -w;
        } else {
            matrix[v * mE + col] = w;
        }
        used++;
    }
}

void IncidenceMatrix::print() const {
    for (int i = 0; i < nV; ++i) {
        for (int j = 0; j < used; ++j) {
            cout << matrix[i * mE + j] << "     ";
        }
        cout << std::endl;
    }
}

