#ifndef AIZO_GRAFS_ADJACENCYLIST_H
#define AIZO_GRAFS_ADJACENCYLIST_H

struct Edge{
    int leadTo; // where the edge leads to
    int weight;
    int nextEdges; // i of the next edge from the same vertex
};

class AdjacencyList{
public:
    int nV; // number of vertexes
    int size; // directed: write once, undirected: write twice
    int used; //how many is in edges[]
    bool directed;

    int* head; //start point
    Edge* edges;
    int* nextNeighbour;

    AdjacencyList(int numberVertexes, int sizeExpected, bool direction);

    ~AdjacencyList();

    void addEdge(int u, int v, int w);

    void print() const;
};

#endif //AIZO_GRAFS_ADJACENCYLIST_H
