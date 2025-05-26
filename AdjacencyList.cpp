#include "AdjacencyList.h"
#include <iostream>
using namespace std;

AdjacencyList::AdjacencyList(int numberVertexes, int sizeExpected, bool direction) {
    nV = numberVertexes;
    directed = direction;
    used = 0;

    if(directed)
        size = sizeExpected;
    else
        size = 2 * sizeExpected;
    
    head = new int[nV];
    edges = new Edge[size];
    nextNeighbour = new int[size];
    
    for (int i = 0; i < nV; i++)  //begining: list is empty
        head[i] = -1;
}

AdjacencyList::~AdjacencyList(){
    delete[] head;
    delete[] edges;
    delete[] nextNeighbour;
}

void AdjacencyList::addEdge(int u, int v, int w) {
    edges[used].leadTo = v;
    edges[used].weight = w;
    nextNeighbour[used] = head[u]; //remember existing neighbour = -1 - no neighbour
    head[u] = used;                //where to look, new link is the first now
    used++;
}

void AdjacencyList::print() const{
    for (int v = 0; v< nV; v++){
        cout << v << ": ";
        int i = head[v];
        while(i != -1){
            cout << "("
            << edges[i].leadTo << ", "
            << edges[i].weight << ") ";
            i = nextNeighbour[i];
        }
        cout << endl;
    }
}

