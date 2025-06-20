#ifndef AIZO_GRAFS_KRUSKALALG_H
#define AIZO_GRAFS_KRUSKALALG_H

#include "../graph/GraphReader.h"
#include "../utils/MinHeap.h"

//class for MST tree to build with Krusklas' alg
class KruskalAlg {
public:

    struct MSTEdge {
        int u, v, w;
    };

    //point to graph adapter
    KruskalAlg(const GraphReader &reader);

    //edges - result in mst, count - how many
    int compute(MSTEdge* edges, int &count);

private:
    const GraphReader* graph;

    struct CycleAvoider {
        int* parent;

        CycleAvoider(int n);
        ~CycleAvoider();

        int find(int x);

        //return true if dif. groups
        bool unite(int a, int b);
    };
};

#endif //AIZO_GRAFS_KRUSKALALG_H


