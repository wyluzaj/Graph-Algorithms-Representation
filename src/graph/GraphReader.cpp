#include "../../include/graph/GraphReader.h"
#include <cmath>


GraphReader::GraphReader(const AdjacencyList &list) {
    listG = &list;
    matG = nullptr;
}

GraphReader::GraphReader(const IncidenceMatrix &mat) {
    listG = nullptr;
    matG = &mat;
}

int GraphReader::numVertices() const {
    if (listG != nullptr) {
        const AdjacencyList &g = *listG;
        return g.nV;
    } else {
        const IncidenceMatrix &g = *matG;
        return g.nV;
    }
}

int GraphReader::numNeighbors(int u) const {
    if (u < 0 || u >= numVertices()) return 0;

    if (listG != nullptr) {
        const AdjacencyList &g = *listG;
        int cnt = 0;
        for (int e = g.headSucc[u]; e != -1; e = g.nextSucc[e]) {
            cnt++;
        }
        return cnt;
    } else {
        const IncidenceMatrix &g = *matG;
        int count = 0;
        for (int col = 0; col < g.used; col++) {
            int val = g.matrix[u * g.mE + col];
            if (g.directed) {
                if (val > 0) count++;
            } else {
                if (val != 0) count++;
            }
        }
        return count;
    }
}

void GraphReader::getNeighbor(int u, int idx, int &v, int &w) const {
    v = -1;
    w = -1;
    if (u < 0 || u >= numVertices()) return;

    if (listG != nullptr) {
        const AdjacencyList &g = *listG;
        int e = g.headSucc[u];
        for (int i = 0; i < idx && e != -1; i++) {
            e = g.nextSucc[e];
        }
        if (e != -1) {
            v = g.edges[e].destination;
            w = g.edges[e].weight;
        }
    } else {
        const IncidenceMatrix &g = *matG;
        int seen = 0;
        for (int col = 0; col < g.used; col++) {
            if (g.directed) {
                // only ++ edges
                if (g.matrix[u * g.mE + col] <= 0) continue;
            } else {
                // undir
                if (g.matrix[u * g.mE + col] == 0) continue;
            }

            for (int row = 0; row < g.nV; row++) {
                if (row != u && g.matrix[row * g.mE + col] != 0) {
                    if (seen == idx) {
                        v = row;
                        w = std::abs(g.matrix[u * g.mE + col]);
                        return;
                    }
                    ++seen;
                    break;
                }
            }
        }
    }
}

