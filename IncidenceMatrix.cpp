#include "IncidenceMatrix.h"
#include <iostream>
using namespace std;

// konstruktor: krok po kroku ustawiamy pola i alokujemy pamięć
IncidenceMatrix::IncidenceMatrix(int vertices, int edgeCapacity, bool isDirected) {
    // ustawiamy liczbę wierzchołków i krawędzi
    nV = vertices;
    mE = edgeCapacity;

    // początkowo nie dodaliśmy żadnej krawędzi
    used = 0;

    // czy graf jest skierowany
    directed = isDirected;

    // alokujemy bufor o rozmiarze nV * mE i zerujemy go
    mat = new int[nV * mE];
    for (int i = 0; i < nV * mE; ++i) {
        mat[i] = 0;
    }
}

// destruktor: zwalniamy jedyny bufor
IncidenceMatrix::~IncidenceMatrix() {
    delete[] mat;
}

// dodaje krawędź u→v z wagą w
void IncidenceMatrix::addEdge(int u, int v, int w) {
    // sprawdzamy, czy mamy miejsce na kolejną krawędź
    if (used < mE) {
        int col = used;  // numer kolumny = index kolejnej krawędzi

        // wiersz u, kolumna col = w
        mat[u * mE + col] = w;

        // wiersz v, kolumna col = -w jeśli skierowany, inaczej w
        if (directed) {
            mat[v * mE + col] = -w;
        } else {
            mat[v * mE + col] = w;
        }

        // oznaczamy, że dodaliśmy jedną krawędź więcej
        used = used + 1;
    }
}

// wypisuje macierz incydencji (kolumny 0..used-1)
void IncidenceMatrix::print() const {
    for (int i = 0; i < nV; ++i) {
        for (int j = 0; j < used; ++j) {
            cout << mat[i * mE + j] << " ";
        }
        cout << std::endl;
    }
}

