#ifndef AIZO_GRAFS_DATAREADER_H
#define AIZO_GRAFS_DATAREADER_H
#include <iostream>
#include <fstream>
#include <string>
#include "AdjacencyList.h"
#include "IncidenceMatrix.h"

template<typename Graph>
class DataReader {
public:

    bool readFromFile(const std::string& filename, Graph& g) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Can't open file: " << filename << "\n";
            return false;
        }

        int n, m;
        file >> m >> n;

        int u, v, w;
        for (int i = 0; i < m; ++i) {
            file >> u >> v >> w;
            g.addEdge(u, v, w);
            if (!g.directed)
                g.addEdge(v, u, w);
        }
        file.close();
        return true;
    }
};



#endif //AIZO_GRAFS_DATAREADER_H
