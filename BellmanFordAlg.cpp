#include "include/BellmanFordAlg.h"
#include <climits>

BellmanFordAlg::BellmanFordAlg(const GraphReader &reader) {
    graph = &reader;
}

bool BellmanFordAlg::compute(int src, int dist[], int parent[]) {
    const GraphReader &G = *graph;//reference
    int n = G.numVertices();

    //rout infinity at the begining
    for (int i = 0; i < n; ++i) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[src] = 0; // source to source route 0

    //n -1 iterations
    for (int pass = 1; pass < n; ++pass) {
        for (int u = 0; u < n; ++u) {
            if (dist[u] == INT_MAX) continue; //skip
            int deg = G.numNeighbors(u);
            for (int k = 0; k < deg; ++k) {
                int v, w;
                G.getNeighbor(u, k, v, w);
                if (dist[u] + w < dist[v]) { //if new rout < then write new
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                }
            }
        }
    }

    return true;
}

