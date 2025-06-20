#include "../../include/algorithms/KruskalAlg.h"

KruskalAlg::KruskalAlg(const GraphReader &reader) {
    graph = &reader;
}

int KruskalAlg::compute(MSTEdge* edges, int &count) {
    const GraphReader &g = *graph;
    int n = g.numVertices(); //vertexes
    CycleAvoider dsu(n); //to avoid cycles
    MinHeap heap;

    bool* visited = new bool[n * n]();
    for (int u = 0; u < n; ++u) {
        int deg = g.numNeighbors(u);
        for (int i = 0; i < deg; ++i) {
            int v, w;
            g.getNeighbor(u, i, v, w); //get neighbour
            if (v >= 0 && !visited[u * n + v] && !visited[v * n + u]) {
                //if neigh. exists and edge not visited both sides then add
                visited[u * n + v] = true;
                visited[v * n + u] = true;
                heap.insert(HeapEdge{u, v, w});
            }
        }
    }
    delete[] visited;

    int cost = 0;
    int used = 0;
    while (used < n - 1 && !heap.isEmpty()) {
        HeapEdge he = heap.extractMin();
        if (dsu.unite(he.from, he.to)) { //must be 2 dif. "groups" of edges - avoiding cycles
            edges[used].u = he.from;
            edges[used].v = he.to;
            edges[used].w = he.weight;
            cost += he.weight;
            ++used;
        }
    }

    //is there mst
    if (used == n - 1) {
        count = used;
        return cost;
    } else {
        count = -1;
        return -1;
    }
}


KruskalAlg::CycleAvoider::CycleAvoider(int n) {
    parent = new int[n];
    for (int i = 0; i < n; ++i)
        parent[i] = i; //begining vertex parent = this vertex
}

KruskalAlg::CycleAvoider::~CycleAvoider() {
    delete[] parent;
}

int KruskalAlg::CycleAvoider::find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

//return true if dif. groups
bool KruskalAlg::CycleAvoider::unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    parent[b] = a;
    return true;
}

