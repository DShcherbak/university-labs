#include <iostream>
#include <cmath>
#include <algorithm>
#include "matrix_graph.h"
#include "bool_graph.h"
//(1,3)  10
// 11 15 18 19 21

int main() {
    Graph_matrix* GM = new Graph_matrix(5,5,true);
    print_graph(GM);
 //   make_transit(GM);
 //   print_graph(GM);
    Graph_bool* GB = new Graph_bool(7,5);
    print_graph(GB);
 //   make_transit(GB);
 //   print_graph(GB);
    std::vector <bool> visited;
    visited.resize(GB->vertices,false);
   /* std::cout << "Debth-first-search (demonstrantes all components of graph):\n";
    for(int i = 0; i < GM->vertices; i++){
        if(!visited[i]){
            dfs(GM,i,visited);
            std::cout << "\n";
        }
    }*/
    std::cout << "Debth-first-search (possible for both graphs, \nbut counting components only in non-oriented):\n";
    for(int i = 0; i < GB->vertices; i++){
        if(!visited[i]){
            dfs(GB,i,visited);
            std::cout << "\n";
        }
    }
    int start;
    std::cout << "Dijkstra algorithm (for non-oriented graph)\n";
    std::cout << "Enter starting vertex for the algorithm please:";
    std::cin >> start;
    Dijkstra(GB,start);
    std::cout << "Distances from " << start << " to:\n";
    for(int i = 0, n = GB->vertices; i < n; i++)
        std::cout << i << " : " << GB->min_dist[start][i] << "\n";
    std::cout << "Topsort (for oreinted graph):"

    return 0;
}