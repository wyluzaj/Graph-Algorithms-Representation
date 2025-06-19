#ifndef AIZO_GRAFS_ADJACENCYLIST_H
#define AIZO_GRAFS_ADJACENCYLIST_H

struct Edge{
    int destination; // where the edge leads to
    int weight;
    int source;
};

class AdjacencyList{
public:
    int nV; // number of vertexes
    int size; // directed: write once, undirected: write twice
    int used; //how many is in edges[]
    bool directed;

    int* headSucc; //start point
    int* headPred;
    Edge* edges; // egde(dest, weight)
    int* nextSucc;
    int* nextPred;

    AdjacencyList(int Vertexes, int Edges, bool isDirected);

    ~AdjacencyList();

    void addEdge(int u, int v, int w);

    void print() const;
};

#endif //AIZO_GRAFS_ADJACENCYLIST_H
