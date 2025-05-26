#include <iostream>
#include <fstream>
#include <string>
#include "include/AdjacencyList.h"
#include "include/IncidenceMatrix.h"
#include "include/GraphGenerator.h"
#include "include/DataReader.h"

int main() {
    using namespace std;

    int mode;
    cout << "Choose:\n"
         << " 1  read from file\n"
         << " 2  generate random\n> ";
    cin >> mode;

    if (mode == 1) {

        string filename;
        cout << "Give filename: ";
        cin  >> filename;

        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Can't open file: " << filename << "\n";
            return -1;
        }

        int n, m;
        file >> m >> n;
        file.close();

        bool directed = false;
        AdjacencyList list(n, m, directed);
        IncidenceMatrix mat(n, m, directed);

        DataReader<AdjacencyList> rdrList;
        if (!rdrList.readFromFile(filename, list)) return -1;

        DataReader<IncidenceMatrix> rdrMat;
        if (!rdrMat.readFromFile(filename, mat)) return -1;

        cout << "\nAdjacency List:\n";
        list.print();

        cout << "\nIncidence Matrix:\n";
        mat.print();
    }
    else if (mode == 2) {

        int vertexes;
        int edges;
        bool directed;
        cout << "Vertexes: ";
        cin >> vertexes;
        cout << "Edges: ";
        cin >> edges;
        cout << "Which (1 dir, 0 undir): ";
        cin >> directed;

        GraphGenerator generator(vertexes);

        AdjacencyList list(vertexes, edges, directed);
        IncidenceMatrix mat(vertexes, edges, directed);

        generator.makeAdjacencyList(list, edges, directed);
        generator.makeIncidenceMatrix(mat, edges, directed);

        cout << "\nAdjacency List:\n";
        list.print();

        cout << "\nIncidence Matrix::\n";
        mat.print();
    }
    else {
        cerr << "Dont know what to do\n";
        return 1;
    }

    return 0;
}
