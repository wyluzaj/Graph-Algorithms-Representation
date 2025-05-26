#ifndef AIZO_GRAFS_INCIDENCEMATRIX_H
#define AIZO_GRAFS_INCIDENCEMATRIX_H

#include <iostream>

class IncidenceMatrix {
public:
    int nV;         // liczba wierzchołków
    int mE;         // maksymalna liczba krawędzi
    int used;       // ile krawędzi już dodano
    bool directed;  // czy graf jest skierowany
    int* mat;       // jednowymiarowy bufor o rozmiarze nV * mE

    // konstruktor
    IncidenceMatrix(int vertices, int edgeCapacity, bool isDirected);

    // destruktor
    ~IncidenceMatrix();

    // dodaje krawędź jako kolejną kolumnę [used]
    void addEdge(int u, int v, int w);

    // wypisuje tylko kolumny od 0 do used-1
    void print() const;
};

#endif //AIZO_GRAFS_INCIDENCEMATRIX_H
