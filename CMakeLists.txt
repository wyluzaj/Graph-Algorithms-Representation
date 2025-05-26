cmake_minimum_required(VERSION 3.26)
project(AIZO_grafs)

set(CMAKE_CXX_STANDARD 17)

add_executable(AIZO_grafs main.cpp
        AdjacencyList.h
        AdjacencyList.cpp
        GraphGenerator.h
        GraphGenerator.cpp
        IncidenceMatrix.h
        IncidenceMatrix.cpp
        Timer.cpp
        Timer.h)
