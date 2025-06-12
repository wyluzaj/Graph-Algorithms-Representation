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
    cout << " 1  read from file\n"
         << " 2  generate random\n";
    cout << "Choose: ";
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

        int vert, edg;
        file >> edg >> vert;
        file.close();

        bool directed = true; //which graf do you have in your file

        //checck edges
        int minEdges;
        if (directed) {
            minEdges = 2 * (vert - 1);
        } else {
            minEdges = vert - 1;
        }
        if (edg < minEdges) {
            cerr << "Min number of edges for direkted graph: 2(vert-1)\n"
                  <<"Min number of edges for undirekted graph: (vert-1)";
            return 1;
        }
        AdjacencyList list(vert, edg, directed);
        IncidenceMatrix mat(vert, edg, directed);

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

        int vert;
        int edg;
        bool directed;
        cout << "Vertexes: ";
        cin >> vert;
        cout << "Edges: ";
        cin >> edg;
        cout << "Which (1 dir, 0 undir): ";
        cin >> directed;

        int minEdges;
        if (directed) {
            minEdges = 2 * (vert - 1);
        } else {
            minEdges = vert - 1;
        }
        if (edg < minEdges) {
            cerr << "Min number of edges for direkted graph: 2(vert-1)\n"
                 <<"Min number of edges for undirekted graph: (vert-1)";
            return 1;
        }

        GraphGenerator generator(vert);

        AdjacencyList list(vert, edg, directed);
        IncidenceMatrix mat(vert, edg, directed);

        generator.makeAdjacencyList(list, edg, directed);
        generator.makeIncidenceMatrix(mat, edg, directed);

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
