cmake_minimum_required(VERSION 3.13)
project(Lab_1)

set(CMAKE_CXX_STANDARD 14)


add_executable(Lab_1 main.cpp
        sources/interactive.cpp headers/interactive.h
        headers/folder.h sources/folder.cpp
        headers/my_file.h sources/my_file.cpp
        headers/tree_node.h sources/tree_node.cpp includes/tree_node.inc
        headers/binary_node.h sources/binary_node.cpp includes/binary_node.inc
        )