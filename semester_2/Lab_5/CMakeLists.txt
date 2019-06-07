cmake_minimum_required(VERSION 3.14)
project(Lab_5)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab_5 main.cpp
        matrix_graph.h
        bool_graph.h
        matrix_graph.cpp
        bool_graph.cpp )