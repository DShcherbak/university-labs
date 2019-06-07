#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include "matrix_graph.h"
#include "bool_graph.h"
//(1,3)  10
// 11 15 18 19 21

void interactive(){
    std::cout << "Hello, dear user!\n";
    Graph_bool* GB = nullptr;
    Graph_matrix* GM = nullptr;
    char key; char temp, graph_type; int V , E;
    bool oriented, weighted;

    while(true){
        std::cout << "Here's list of your options:\n";
        std::cout << "Enter \"n\" to create a new graph of V vertices and E edges\n";
        std::cout << "Enter \"d\" to perform Dijkstra algorithm\n";
        std::cout << "Enter \"t\" to perform topological sort to one of graphs\n";
        std::cout << "Enter \"p\" to print one of the graphs\n";
        std::cout << "Enter \"m\" to find minimum spanning tree (Kruskala algorithm)\n";
        std::cout << "Enter \"q\" to quit.\n";
        std::cin >> key;
        if(key == 'q'){
            std::cout << "Good bye!\n";
            return;
        }
        else {
            std::cout << "You should choose operand for your function.\n";
            std::cout << "Enter 0 to choose graph, represented by array of integers.\n";
            std::cout << "(using binary operations)\n";
            std::cout << "Enter anything else for matrix-graph.\n";
            std::cin >> graph_type;
        }
        switch(key){
            case 'n':
                std::cout << "Enter number of vertices:";
                std::cin >> V;
                std::cout << "Enter number of edges:";
                std::cin >> E;
                std::cout << "Should graph be oriented? (y/n)";
                std::cin >> temp;
                oriented = (temp == 'y' || temp == 'Y');
                if(graph_type != '0'){
                    std::cout << "Should graph be weighted? (y/n)";
                    std::cin >> temp;
                    weighted = (temp == 'y' || temp == 'Y');
                }
                if(graph_type == '0'){
                    delete GB;
                    GB = new Graph_bool(V,E,oriented);
                }
                else{
                    delete GM;
                    GM = new Graph_matrix(V,E,oriented,weighted);
                }
                break;
            case 'd':
                if(graph_type == '0' || !GM->is_weight){
                    std::cout << "Algorithm only possible for weigted graphs!\n";
                    break;
                }
                std::cout << "Enter starting point for the algorithm:";
                std::cin >> V;
                Dijkstra(GM,V);
                std::cout << "Distances from " << V << " to:\n";
                for(int i = 0, n = GM->vertices; i < n; i++)
                    std::cout << i << " : " << (GM->min_dist[V][i] == inf ? "inf" : std::to_string(GM->min_dist[V][i]))  << "\n";
                break;
            case 't':
                if(graph_type == '0'){
                    if(!GB->is_oriented){
                        std::cout << "Algorithm only possible for oriented graphs!\n";
                        break;
                    }
                    topsort(GB);
                    for(int v : GB->top_sort)
                        std::cout << v << " ";
                    std::cout << std::endl;
                }
                else{
                    if(!GM->is_oriented){
                        std::cout << "Algorithm only possible for oriented graphs!\n";
                        break;
                    }
                    topsort(GM);
                    for(int v : GM->top_sort)
                        std::cout << v << " ";
                    std::cout << std::endl;
                }
            case 'p':
                if(graph_type == '0')
                    print_graph(GB);
                else
                    print_graph(GM);
                break;

            case 'm':
                if(graph_type == '0' || !GM->is_weight){
                    std::cout << "Algorithm only possible for weigted graphs!\n";
                    break;
                }
                std::cout << "Minimum spanning tree (for non-oriented graph):" << std::endl;
                Kruskala(GM);
                break;
            case 'q':
                delete GB;
                delete GM;
                return;

            default:
                std::cout << "No such command.\n";
                break;
        }
    }
}

int demo() {
    Graph_matrix* GM = new Graph_matrix(10,12,false,true);
    print_graph(GM);
 //   make_transit(GM);
 //   print_graph(GM);
    Graph_bool* GB = new Graph_bool(8,6,true);
    print_graph(GB);
 //   make_transit(GB);
 //   print_graph(GB);
    std::vector <bool> visited;
    visited.resize(GM->vertices,false);

    std::cout << "Debth-first-search (possible for both graphs, \nbut counting components only in non-oriented):\n";
    for(int i = 0; i < GM->vertices; i++){
        if(!visited[i]){
            dfs(GM,i,visited);
            std::cout << "\n";
        }
    }
    int start;
    std::cout << "Dijkstra algorithm (for non-oriented graph)\n";
    std::cout << "Enter starting vertex for the algorithm please:";
    std::cin >> start;
    Dijkstra(GM,start);
    std::cout << "Distances from " << start << " to:\n";
    for(int i = 0, n = GM->vertices; i < n; i++)
    std::cout << i << " : " << (GM->min_dist[start][i] == inf ? "inf" : std::to_string(GM->min_dist[start][i])) << "\n";
  std::cout << "Topsort (for oreinted graph):";
    topsort(GB);
    for(int v : GB->top_sort)
        std::cout << v << " ";
    std::cout << std::endl;

    std::cout << "Spanning tree (for non-oriented graph):\n";

    for(int i = 0; i < GM->vertices; i++)
        visited[i] = false;
    for(int i = 0; i < GM->vertices; i++) {
        if (!visited[i]) {
            span_dfs(GM, i, visited);
            std::cout << "\n";
        }
    }

    std::cout << "Minimum spanning tree (for non-oriented graph):" << std::endl;
    Kruskala(GM);
    return 0;
}

int main() {
    int key;
    while(true) {
        std::cout << "MAIN MENU\n";
        std::cout << "Please, choose your mode:\n";
        std::cout << "Press 1 for interactive mode.\n";
        std::cout << "Press 2 for demonstration mode.\n";
        std::cout << "Press 3 to exit the program\n";
        std::cin >> key;
        switch(key){
            case 1:
                interactive();
                return 0;
            case 2:
                demo();
                return 0;
            case 3:
                return 0;
            default:
                std::cout << "Try another command!\n";

        }
    }
}