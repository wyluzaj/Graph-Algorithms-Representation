#include "GraphGenerator.h"
#include <algorithm>

GraphGenerator::GraphGenerator(int vertexCount) {
    std::random_device rd;
    rng = std::mt19937(rd());
    weightDist = std::uniform_int_distribution<int>(0, 100);
    vertexDist = std::uniform_int_distribution<int>(0, vertexCount - 1);
}
//shuffle using Fisher–Yates shuffle Algorithm
void GraphGenerator::shuffle(int *arr, int size) {
    for (int i =0; i< size; i++)
        arr[i] = i;
    for(int i = size -1; i > 0; i--){
        int j = vertexDist(rng) % (i + 1);// random from 0 to i
        std::swap(arr[i], arr[j]);
    }
}
void GraphGenerator::makeGraph(AdjacencyList& graph, int m, bool directed) {
    int n      = graph.nV;
    int mMin   = n - 1;
    int mMax   = directed;

    //max number of edges
    if(directed)
        mMax = n * (n-1); //directed graph
    else
        mMax = n * (n-1) /2; //undirected graph

   if (m < mMin || m > mMax){
       return; //empty graph
   }
    bool* used = new bool[n * n]; //table for existing edges
    for (int i = 0; i < n * n; ++i)
        used[i] = false;

    // build spanning tree (n-1) edges
    int* perm = new int[n];
    shuffle(perm, n);

    for(int i = 0; i < n -1; i++){
        int u = perm[i];
        int v = perm[i + 1];
        int w = weightDist(rng);
        graph.addEdge(u, v, w);
        if (!directed) // if notdirected add another edge
            graph.addEdge(v, u, w);

        used[u * n + v] = true;
        if (!directed)
            used[v * n + u] = true;
    }
    int added = n - 1;
    while (added < m) {

        int u = vertexDist(rng);
        int v = vertexDist(rng);

        if (u == v || used[u * n + v] || (!directed && used[v * n + u]))
            continue; //if smth = true -> skip go to the begining
        //a. no loops b. skip existing  c. skip existing in undirected

        int w = weightDist(rng);

        graph.addEdge(u, v, w);
        used[u * n + v] = true;

        if (!directed) {
            graph.addEdge(v, u, w);
            used[v * n + u] = true;
        }

        ++added;
    }
    delete[] used;
    delete[] perm;
}

