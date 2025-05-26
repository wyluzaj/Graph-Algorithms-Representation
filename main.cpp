#include <iostream>
#include "GraphGenerator.h"

int main() {
    int n = 10;
    int m = 20;
    bool directed = false;

    GraphGenerator generator(n);

    AdjacencyList graph(n, m, directed);
    generator.makeGraph(graph, m, directed);

    std::cout << "Wygenerowany graf:\n";
    graph.print();
    return 0;
}
