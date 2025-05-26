cmake_minimum_required(VERSION 3.26)
project(AIZO_grafs)

set(CMAKE_CXX_STANDARD 17)

add_executable(AIZO_grafs main.cpp
        include/AdjacencyList.h
        AdjacencyList.cpp
        include/GraphGenerator.h
        GraphGenerator.cpp
        include/IncidenceMatrix.h
        IncidenceMatrix.cpp
        Timer.cpp
        include/Timer.h
        include/DataReader.h
)
