#ifndef AIZO_GRAFS_ADJACENCYLIST_H
#define AIZO_GRAFS_ADJACENCYLIST_H

struct Edge{
    int destination; // where the edge leads to
    int weight;
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

    AdjacencyList(int numberVertexes, int sizeExpected, bool isDirected);

    ~AdjacencyList();

    void addEdge(int u, int v, int w);

    void print() const;
};

#endif //AIZO_GRAFS_ADJACENCYLIST_H
