#include "../../include/algorithms/DijkstraAlg.h"
#include <climits>

DijkstraAlg::DijkstraAlg(const GraphReader &adapter) {
    graph = &adapter;
}

void DijkstraAlg::compute(int src, int dist[], int parent[]) {
    const GraphReader &G = *graph;
    int n = G.numVertices();

    bool *visited = new bool[n];
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
        dist[i]    = INT_MAX;
        parent[i]  = -1;
    }

    MinHeap heap;

    //source
    HeapEdge start;
    start.from   = -1;
    start.to     = src;
    start.weight = 0;
    heap.insert(start);

    while (!heap.isEmpty()) {
        HeapEdge e = heap.extractMin();
        int u = e.to;
        int d = e.weight;
        if (visited[u]) continue;
        visited[u] = true;
        dist[u]    = d;
        parent[u]  = e.from;

        int deg = G.numNeighbors(u);
        for (int i = 0; i < deg; ++i) {
            int v, w;
            G.getNeighbor(u, i, v, w);
            if (!visited[v]) {
                HeapEdge ne;
                ne.from   = u;
                ne.to     = v;
                ne.weight = d + w;
                heap.insert(ne);
            }
        }
    }

    delete[] visited;
}
