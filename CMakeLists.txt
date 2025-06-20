cmake_minimum_required(VERSION 3.26)
project(AIZO_grafs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(AIZO_grafs main.cpp
        include/graph/AdjacencyList.h
        src/graph/AdjacencyList.cpp
        include/graph/GraphGenerator.h
        src/graph/GraphGenerator.cpp
        include/graph/IncidenceMatrix.h
        src/graph/IncidenceMatrix.cpp
        src/utils/Timer.cpp
        include/utils/Timer.h
        include/utils/DataReader.h
        src/algorithms/BellmanFordAlg.cpp
        src/algorithms/KruskalAlg.cpp
        src/utils/MinHeap.cpp
        src/graph/CheckGraph.cpp
        src/graph/GraphReader.cpp
        src/algorithms/DijkstraAlg.cpp
        src/algorithms/PrimAlg.cpp
)
set_target_properties(AIZO_grafs PROPERTIES
        LINK_FLAGS "-static -pthread -static-libgcc -static-libstdc++"
)