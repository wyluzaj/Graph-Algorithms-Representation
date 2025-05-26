#include <iostream>
#include "GraphGenerator.h"
#include "IncidenceMatrix.h"
using namespace std;

int main() {
    int n = 5;
    int m = 4;
    bool directed = false;

    GraphGenerator generator(n);

    AdjacencyList graph(n, m, directed); //empty graph
    generator.makeAdjacencyList(graph, m, directed);

    cout << "Adjacency List:\n";
    graph.print();


    IncidenceMatrix mat(n, m, directed);
    generator.makeIncidenceMatrix(mat, m, directed);
    cout << "\nIncidence Matrix:\n";
    mat.print();
    return 0;
}
