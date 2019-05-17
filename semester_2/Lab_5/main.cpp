#include <iostream>
#include <cmath>
#include <algorithm>
#include "matrix_graph.h"
#include "bool_graph.h"
//(1,3)  10
// 11 15 18 19 21

int main() {
    Graph_matrix GM = *(new Graph_matrix(5,5,true));
    print_graph(GM);
    make_transit(GM);
    print_graph(GM);
    Graph_bool GB = *(new Graph_bool(7,3));
    print_graph(GB);
    make_transit(GB);
    print_graph(GB);
    std::vector <bool> visited;
    visited.resize(GB.vertices,false);
    std::cout << "Debth-first-search (demonstrantes all components of graph):\n";

    std::cout << "Debth-first-search (now for a graph represented as vector of bool arrays):\n";
    for(int i = 0; i < GB.vertices; i++){
        if(!visited[i]){
            dfs(GB,i,visited);
            std::cout << "\n";
        }
    }

    return 0;
}