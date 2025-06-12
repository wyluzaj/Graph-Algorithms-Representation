#include "include/GraphGenerator.h"
#include "include/IncidenceMatrix.h"
#include "include/AdjacencyList.h"
#include <algorithm>
#include <random>

GraphGenerator::GraphGenerator(int vertexCount) {
    std::random_device rd;
    rng = std::mt19937(rd());
    weightDist = std::uniform_int_distribution<int>(0, 100);
    vertexDist = std::uniform_int_distribution<int>(0, vertexCount - 1);
}

static int randInt(std::mt19937& rng, int i) {
    std::uniform_int_distribution<int> dist(0, i);
    return dist(rng);
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
void GraphGenerator::makeAdjacencyList(AdjacencyList& list, int m, bool directed) {

    int n = list.nV;

    int mMin;
    //min edges
    if (directed){
        mMin = 2 * (n-1);
    }else{
        mMin = n - 1;
    }

    int mMax;
    //max number of edges
    if(directed)
        mMax = n * (n-1); //directed list
    else
        mMax = n * (n-1) /2; //undirected list

   if (m < mMin || m > mMax){
       return; //empty list
   }

    bool* used = new bool[n * n]; //table for existing edges
    for (int i = 0; i < n * n; ++i)
        used[i] = false;

    int* perm = new int[n];
    shuffle(perm, n);
    int added;

    if (directed){ //build v1->v2->v3 from root to another vertexes
        for(int i = 1; i<n;i++){
            int parentIndex = randInt(rng, i-1);
            int u = perm[parentIndex];
            int v = perm[i];
            int w = weightDist(rng);
            list.addEdge(u, v, w);
            used[u*n + v] = true;
        }
        for (int i = 1; i < n; ++i) { //build from vertexes to root
            int parentIndex = randInt(rng, i-1);
            int u = perm[i];
            int v = perm[parentIndex];
            int w = weightDist(rng);
            list.addEdge(u, v, w);
            used[u*n + v] = true;
        }
        added = 2 * (n-1);

    } else{
        for (int i = 0; i < n - 1; ++i) {
            int u = perm[i];
            int v = perm[i + 1];
            int w = weightDist(rng);
            list.addEdge(u, v, w);
            list.addEdge(v, u, w);
            used[u * n + v] = true;
            used[v * n + u] = true;
        }
        added = n - 1;
    }

    while (added < m) {

        int u = vertexDist(rng);
        int v = vertexDist(rng);

        if (u == v || used[u * n + v] || (!directed && used[v * n + u]))
            continue; //if smth = true -> skip go to the begining
        //a. no loops b. skip existing  c. skip existing in undirected

        int w = weightDist(rng);

        list.addEdge(u, v, w);
        used[u * n + v] = true;

        if (!directed) {
            list.addEdge(v, u, w);
            used[v * n + u] = true;
        }

        ++added;
    }
    delete[] used;
    delete[] perm;
}


void GraphGenerator::makeIncidenceMatrix(IncidenceMatrix& matrix, int m, bool directed){

    int n = matrix.nV;

    int mMin;
    if (directed){
        mMin = 2 * (n-1);
    }else{
        mMin = n - 1;
    }

    int mMax;
    //max number of edges
    if(directed)
        mMax = n * (n-1); //directed list
    else
        mMax = n * (n-1) /2; //undirected list

    if (m < mMin || m > mMax){
        return; //empty list
    }

    bool* used = new bool[n * n];
    for (int i = 0; i < n * n; ++i)
        used[i] = false;

    //spanning tree
    int* perm = new int[n];
    shuffle(perm, n);

    int added;

    if (directed){ //build v1->v2->v3 from root to another vertexes
        for(int i = 1; i<n;i++){
            int parentIndex = randInt(rng, i-1);
            int u = perm[parentIndex];
            int v = perm[i];
            int w = weightDist(rng);
            matrix.addEdge(u, v, w);
            used[u*n + v] = true;
        }
        for (int i = 1; i < n; ++i) { //build from vertexes to root
            int parentIndex = randInt(rng, i-1);
            int u = perm[i];
            int v = perm[parentIndex];
            int w = weightDist(rng);
            matrix.addEdge(u, v, w);
            used[u*n + v] = true;
        }
        added = 2 * (n-1);

    } else{
        for (int i = 0; i < n - 1; ++i) {
            int u = perm[i];
            int v = perm[i + 1];
            int w = weightDist(rng);
            matrix.addEdge(u, v, w);
            matrix.addEdge(v, u, w);
            used[u * n + v] = true;
            used[v * n + u] = true;
        }
        added = n - 1;
    }

    while (added < m) {

        int u = vertexDist(rng);
        int v = vertexDist(rng);

        if (u == v || used[u * n + v] || (!directed && used[v * n + u]))
            continue; //if smth = true -> skip go to the begining
        //a. no loops b. skip existing  c. skip existing in undirected

        int w = weightDist(rng);

        matrix.addEdge(u, v, w);
        used[u * n + v] = true;

        if (!directed) {
            matrix.addEdge(v, u, w);
            used[v * n + u] = true;
        }

        ++added;
    }
    delete[] used;
    delete[] perm;
}



