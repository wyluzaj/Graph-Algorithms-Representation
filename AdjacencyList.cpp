#include "include/AdjacencyList.h"
#include <iostream>
using namespace std;

AdjacencyList::AdjacencyList(int Vertexes, int Edges, bool isDirected) {

    nV = Vertexes;
    directed = isDirected;
    used = 0;

    if(directed)
        size = Edges;
    else
        size = 2 * Edges;

    headSucc = new int[nV];
    headPred = new int[nV];
    edges = new Edge[size];
    nextSucc = new int[size];
    nextPred = new int[size];
    
    for (int i = 0; i < nV; i++)  //begining: list is empty
        headSucc[i] = -1;

    for (int i = 0; i < nV; i++)  //begining: list is empty
        headPred[i] = -1;
}

AdjacencyList::~AdjacencyList(){
    delete[] headSucc;
    delete[] headPred;
    delete[] edges;
    delete[] nextSucc;
    delete[] nextPred;
}

void AdjacencyList::addEdge(int u, int v, int w) {
    if (used >= size) return; // try too not overbook
    edges[used].destination = v;
    edges[used].weight = w;
    edges[used].source      = u;
    nextSucc[used] = headSucc[u]; //headSucc = i of the nei. remember existing neighbour = -1 - no neighbour
    headSucc[u] = used;                //where to look, new link is the first now
    nextPred[used] = headPred[v];
    headPred[v] = used;
    used++;
}

void AdjacencyList::print() const{
    std::cout << "succ || pred\n";
    for (int u = 0; u < nV; ++u) {
        std::cout << u << ":";
        for (int i = headSucc[u]; i != -1; i = nextSucc[i]) {
            std::cout << " (" << edges[i].destination
                      << "," << edges[i].weight << ")";
        }
        std::cout << " || ";
        for (int i = headPred[u]; i != -1; i = nextPred[i]) {
            std::cout << " (" << edges[i].source
                      << "," << edges[i].weight << ")";
        }
        std::cout << "\n";
    }
}

