#include "include/PrimAlg.h"



PrimAlgorithm::PrimAlgorithm(const GraphReader &adapter) {
    graphPtr = &adapter;
}


int PrimAlgorithm::compute(int parent[]) {
    const GraphReader &graph = *graphPtr;
    int n = graph.numVertices();  // number of vetexes

    //track if a vertex is already in the MST
    bool *inMST = new bool[n];
    for (int i = 0; i < n; i++) {
        inMST[i] = false;
        parent[i] = -1;
    }

    MinHeap heap;

    //start vertex 0
    inMST[0] = true;

    //insert all neighbors of starting vertex into the heap
    int deg0 = graph.numNeighbors(0);
    for (int i = 0; i < deg0; ++i) {
        int v, w;
        graph.getNeighbor(0, i, v, w);
        HeapEdge he;
        he.from = 0;
        he.to = v;
        he.weight = w;
        heap.insert(he);
    }

    int used = 0;  //number of edges used in MST
    int cost = 0;  //weight of the MST

    // n - 1 edges in MST or heap is empty
    while (used < n - 1 && !heap.isEmpty()) {
        HeapEdge he = heap.extractMin();
        int u = he.to;
        if (inMST[u]) continue;  //skip if vertex in MST

        //include vertex in MST
        inMST[u] = true;
        parent[u] = he.from;
        cost += he.weight;
        ++used;

        //add all valid neighbors of u to heap
        int du = graph.numNeighbors(u);
        for (int i = 0; i < du; ++i) {
            int v2, w2;
            graph.getNeighbor(u, i, v2, w2);
            if (!inMST[v2]) {
                HeapEdge he2;
                he2.from = u;
                he2.to = v2;
                he2.weight = w2;
                heap.insert(he2);
            }
        }
    }

    delete[] inMST;

    // If MST is complete, return its cost; otherwise -1
    return (used == n - 1 ? cost : -1);
}

