#include <iostream>
#include <fstream>
#include <string>
#include "include/graph/AdjacencyList.h"
#include "include/graph/IncidenceMatrix.h"
#include "include/graph/GraphGenerator.h"
#include "include/graph/GraphReader.h"
#include "include/utils/Timer.h"
#include "include/utils/DataWriter.h"
#include "include/graph/CheckGraph.h"
#include "include/algorithms/PrimAlg.h"
#include "include/algorithms/KruskalAlg.h"
#include "include/algorithms/DijkstraAlg.h"
#include "include/algorithms/BellmanFordAlg.h"

enum problem { MST = 0, SHORTEST_PATH = 1 };
enum MSTAlgorithm { ALLMST = 0, PRIM = 1, KRUSKAL = 2 };
enum SPAlgorithm { ALLSP = 0, DIJKSTRA = 1, BELLMAN = 2 };

void printHelp() {
    std::cout << R"(Usage:

FILE TEST MODE:
  ./YourProject --file <problem> <algorithm> <inputFile> [outputFile]
    <problem>    Problem to solve (e.g. 0 - MST, 1 - shortest path)
    <algorithm>  Algorithm for the problem:
                   For MST:      0 - all, 1 - Prim, 2 - Kruskal
                   For shortest: 0 - all, 1 - Dijkstra, 2 - Bellman–Ford
    <inputFile>  Input file containing the graph.
    [outputFile] Optional. If provided, solved problem will be stored there.

BENCHMARK MODE:
  ./YourProject --test <problem> <algorithm> <size> <density> <count> <outputFile>
    <problem>    Problem to solve (e.g. 0 - MST, 1 - shortest path)
    <algorithm>  Algorithm for the problem:
                   For MST:      0 - all, 1 - Prim, 2 - Kruskal
                   For shortest: 0 - all, 1 - Dijkstra, 2 - Bellman–Ford
    <size>       Number of nodes in the generated graph.
    <density>    Edge density 10/20.. for example.
    <count>      How many times test should be repeated.
    <outputFile> File where the benchmark results will be saved.

HELP MODE:
  ./YourProject --help
    Displays this help message.
)" << std::endl;
}

void printPath(int dst, const int* parent) {
    if (parent[dst] == -1) {
        std::cout << dst;
        return;
    }
    printPath(parent[dst], parent);
    std::cout << " -> " << dst;
}

int calculateEdges(int vertices, double density, bool directed) {
    return directed
           ? static_cast<int>(density * vertices * (vertices - 1) / 100.0)
           : static_cast<int>(density * vertices * (vertices - 1) / 200.0);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp();
        return 1;
    }

    std::string mode = argv[1];

    if (mode == "--help") {
        printHelp();
        return 0;
    }

    if (mode == "--file") {
        if (argc < 5) {
            printHelp();
            return 1;
        }

        int problem = std::stoi(argv[2]);
        int algorithm = std::stoi(argv[3]);
        std::string inputFile = argv[4];
        std::string outputFile = (argc > 5 ? argv[5] : "");
        bool directed = (problem == 1);

        std::ifstream fin(inputFile);
        if (!fin.is_open()) {
            std::cerr << "Cannot open input file.\n";
            return 1;
        }

        int m, n;
        fin >> m >> n;


        AdjacencyList list(n, m, directed);
        IncidenceMatrix mat(n, m, directed);

        for (int i = 0; i < m; ++i) {
            int u, v, w;
            fin >> u >> v >> w;
            //undir for MST
            list.addEdge(u, v, w);
            if (problem == 0) {
                list.addEdge(v, u, w);
            }
            mat.addEdge(u, v, w);

        }

        fin.close();

        if (!CheckGraph::verify(list, list.used / (directed ? 1 : 2)) ||
            !CheckGraph::verify(mat, mat.used)) {
            std::cerr << "Graph failed\n";
            return 1;
        }
        std::cout << "Reading from file - OK.\n\n";

        list.print();
        mat.print();

        GraphReader readerListObj(list);
        GraphReader readerMatObj(mat);
        Timer timer;
        std::ofstream out;
        if (!outputFile.empty()) out.open(outputFile);

        if (problem == MST) {
            if (algorithm == ALLMST || algorithm == PRIM) {
                int* parentList = new int[list.nV];
                int* parentMat  = new int[mat.nV];

                Timer timerList, timerMat;
                timerList.start();
                PrimAlgorithm primList(readerListObj);
                int costList = primList.compute(parentList);
                timerList.stop();

                timerMat.start();
                PrimAlgorithm primMat(readerMatObj);
                int costMat = primMat.compute(parentMat);
                timerMat.stop();

                std::cout << "[Prim - List] MST cost:  " << costList << " Time:  " << timerList.result() << "ms\n";
                std::cout << "[Prim - Matrix] MST cost:  " << costMat << " Time:  " << timerMat.result() << "ms\n";

                delete[] parentList;
                delete[] parentMat;
            }
            if (algorithm == ALLMST || algorithm == KRUSKAL) {
                auto* edgesList = new KruskalAlg::MSTEdge[list.nV - 1];
                auto* edgesMat  = new KruskalAlg::MSTEdge[mat.nV - 1];
                int countList, countMat;

                Timer timerList, timerMat;
                timerList.start();
                KruskalAlg kruskalList(readerListObj);
                int costList = kruskalList.compute(edgesList, countList);
                timerList.stop();

                timerMat.start();
//                std::cout << "\nDEBUG: Kruskal na m\n";
//                std::cout << "Vertices: " << readerMatObj.numVertices() << "\n";
//                std::cout << "Edges used in matrix: " << mat.used << " (declared capacity: " << mat.mE << ")\n";
//
//                for (int u = 0; u < readerMatObj.numVertices(); ++u) {
//                    int deg = readerMatObj.numNeighbors(u);
//                    std::cout << "Vertex " << u << " has " << deg << " neighbors\n";
//                    for (int i = 0; i < deg; ++i) {
//                        int v, w;
//                        readerMatObj.getNeighbor(u, i, v, w);
//                        std::cout << "  -> " << v << " (weight = " << w << ")\n";
//                    }
//                }

                KruskalAlg kruskalMat(readerMatObj);
                int costMat = kruskalMat.compute(edgesMat, countMat);
                timerMat.stop();

                std::cout << "[Kruskal - List] MST cost:  " << costList << " Time:  " << timerList.result() << "ms\n";
                std::cout << "[Kruskal - Matrix] MST cost:  " << costMat << " Time:  " << timerMat.result() << "ms\n";

                delete[] edgesList;
                delete[] edgesMat;
            }
        } else {
            int start, end;
            std::cout << "Enter source vertex: "; std::cin >> start;
            std::cout << "Enter target vertex: "; std::cin >> end;

            if (algorithm == ALLSP || algorithm == DIJKSTRA) {
                int* distList = new int[list.nV];
                int* parentList = new int[list.nV];
                int* distMat = new int[mat.nV];
                int* parentMat = new int[mat.nV];

                Timer timerList, timerMat;
                timerList.start();
                DijkstraAlg dijList(readerListObj);
                dijList.compute(start, distList, parentList);
                timerList.stop();

                timerMat.start();
                DijkstraAlg dijMat(readerMatObj);
                dijMat.compute(start, distMat, parentMat);
                timerMat.stop();

                std::cout << "[Dijkstra - List] Distance =  " << distList[end] << " Time:  " << timerList.result() << "ms\nPath: ";
                printPath(end, parentList); std::cout << "\n";

                std::cout << "[Dijkstra - Matrix] Distance =  " << distMat[end] << " Time:  " << timerMat.result() << "ms\nPath: ";
                printPath(end, parentMat); std::cout << "\n";

                delete[] distList;
                delete[] parentList;
                delete[] distMat;
                delete[] parentMat;
            }

            if (algorithm == ALLSP || algorithm == BELLMAN) {
                int* distList = new int[list.nV];
                int* parentList = new int[list.nV];
                int* distMat = new int[mat.nV];
                int* parentMat = new int[mat.nV];

                Timer timerList, timerMat;
                timerList.start();
                BellmanFordAlg bfList(readerListObj);
                bfList.compute(start, distList, parentList);
                timerList.stop();

                timerMat.start();
                BellmanFordAlg bfMat(readerMatObj);
                bfMat.compute(start, distMat, parentMat);
                timerMat.stop();

                std::cout << "[Bellman-Ford - List] Distance =  " << distList[end] << " Time:  " << timerList.result() << "ms\nPath: ";
                printPath(end, parentList); std::cout << "\n";

                std::cout << "[Bellman-Ford - Matrix] Distance =  " << distMat[end] << " Time:  " << timerMat.result() << "ms\nPath: ";
                printPath(end, parentMat); std::cout << "\n";

                delete[] distList; delete[] parentList;
                delete[] distMat; delete[] parentMat;
            }
        }


        if (out.is_open()) out.close();
        return 0;
    }

    if (mode == "--test") {
        if (argc != 8) {
            std::cerr << "Invalid args\n";
            printHelp();
            return 1;
        }

        int problem = std::stoi(argv[2]);
        int algorithm = std::stoi(argv[3]);
        int size = std::stoi(argv[4]);
        double density = std::stod(argv[5]);
        int count = std::stoi(argv[6]);
        std::string outFile = argv[7];

        bool directed = (problem == 1);
        int edges = calculateEdges(size, density, directed);

        DataWriter writer(outFile);
        Timer timer;

        double sumPrimList = 0, sumPrimMatrix = 0;
        double sumKruskalList = 0, sumKruskalMatrix = 0;
        double sumDijkstraList = 0, sumDijkstraMatrix = 0;
        double sumBellmanList = 0, sumBellmanMatrix = 0;

        for (int i = 0; i < count; ++i) {
            GraphGenerator gen(size);
            AdjacencyList list(size, edges, directed);
            IncidenceMatrix mat(size, edges, directed);
            gen.makeAdjacencyList(list, edges, directed);
            gen.makeIncidenceMatrix(mat, edges, directed);

            GraphReader listR(list);
            GraphReader matR(mat);

//            list.print();
//            mat.print();

            if (problem == MST) {
                if (algorithm == ALLMST || algorithm == PRIM) {
                    // Prim
                    Timer t1; t1.start();
                    PrimAlgorithm primList(listR);
                    int* p1 = new int[size];
                    int costList = primList.compute(p1);
                    t1.stop();
                    sumPrimList += t1.result();

                    Timer t2; t2.start();
                    PrimAlgorithm primMat(matR);
                    int* p2 = new int[size];
                    int costMat = primMat.compute(p2);
                    t2.stop(); sumPrimMatrix += t2.result();


//                    if (costList != costMat) {
//                        std::cout
//                                << "Prim : list cost="
//                                << costList << " matrix cost=" << costMat << "\n";
//                        return 1;
//                    }


                    delete[] p1;
                    delete[] p2;
                }

                if (algorithm == ALLMST || algorithm == KRUSKAL) {
                    //Kruskal
                    Timer t1;
                    t1.start();
                    KruskalAlg krList(listR);
                    auto* edges1 = new KruskalAlg::MSTEdge[size - 1];
                    int countList;
                    int costList = krList.compute(edges1, countList);
                    t1.stop();
                    sumKruskalList += t1.result();

                    Timer t2; t2.start();
                    KruskalAlg krMat(matR);
                    auto* edges2 = new KruskalAlg::MSTEdge[size - 1];
                    int countMat;
                    int costMat = krMat.compute(edges2, countMat);
                    t2.stop();
                    sumKruskalMatrix += t2.result();

//                    if (costList != costMat) {
//                        std::cout
//                                << "Kruskal : list cost="
//                                << costList << " matrix cost=" << costMat << "\n";
//                        return 1;
//                    }

                    delete[] edges1;
                    delete[] edges2;
                }
            } else {
                if (algorithm == ALLSP || algorithm == DIJKSTRA) {
                    Timer t1; t1.start();
                    DijkstraAlg dijList(listR);
                    int* d1 = new int[size], *p1 = new int[size];
                    dijList.compute(0, d1, p1);
                    t1.stop();
                    sumDijkstraList += t1.result();
                    delete[] d1; delete[] p1;

                    Timer t2; t2.start();
                    DijkstraAlg dijMat(matR);
                    int* d2 = new int[size], *p2 = new int[size];
                    dijMat.compute(0, d2, p2);
                    t2.stop();
                    sumDijkstraMatrix += t2.result();
                    delete[] d2; delete[] p2;
                }
                if (algorithm == ALLSP || algorithm == BELLMAN) {
                    Timer t1; t1.start();
                    BellmanFordAlg bfList(listR);
                    int* d1 = new int[size], *p1 = new int[size];
                    bfList.compute(0, d1, p1);
                    t1.stop();
                    sumBellmanList += t1.result();
                    delete[] d1; delete[] p1;

                    Timer t2; t2.start();
                    BellmanFordAlg bfMat(matR);
                    int* d2 = new int[size], *p2 = new int[size];
                    bfMat.compute(0, d2, p2);
                    t2.stop();
                    sumBellmanMatrix += t2.result();
                    delete[] d2; delete[] p2;
                }
            }
        }

        if (problem == MST) {
            // MST
            if (algorithm == ALLMST || algorithm == PRIM)
                writer.write(
                        "MST",   // problem
                        "P",     // Prim
                        size, density, edges, count,
                        sumPrimList/count, sumPrimMatrix/count
                );
            if (algorithm == ALLMST || algorithm == KRUSKAL)
                writer.write(
                        "MST",   // problem
                        "K",     // Kruskal
                        size, density, edges, count,
                        sumKruskalList/count, sumKruskalMatrix/count
                );
        } else {
            // SP
            if (algorithm == ALLSP || algorithm == DIJKSTRA)
                writer.write(
                        "SP",    // shortest path
                        "D",     // Dijkstra
                        size, density, edges, count,
                        sumDijkstraList/count, sumDijkstraMatrix/count
                );
            if (algorithm == ALLSP || algorithm == BELLMAN)
                writer.write(
                        "SP",    // shortest path
                        "B",     // Bellman-Ford
                        size, density, edges, count,
                        sumBellmanList/count, sumBellmanMatrix/count
                );
        }


        return 0;
    }

    std::cerr << "Unknown mode. Use --help.\n";
    return 1;
}
