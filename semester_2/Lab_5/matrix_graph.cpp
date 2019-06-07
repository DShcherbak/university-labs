#include "matrix_graph.h"
#include "bool_graph.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>



int randomInt(int begin, int end) {
    static std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);

}

edge::edge(int f, int t, int c){
        from = f;
        to  = t;
        cost = c;
}

bool operator < (edge a, edge b){
    return a.cost < b.cost;
}


bool operator <= (edge a, edge b){
    return a.cost <= b.cost;
}

Graph_matrix::Graph_matrix(int vert, int cnt_edge, bool is_orient, bool is_wght)
{
    int from;
    int to;
    vertices = vert;
    is_oriented = is_orient;
    is_weight = is_wght;
    for(int i = 0; i < vertices; i++)
        for(int j = 0; j < vertices; j++)
            min_dist[i][j] = inf;
    while(cnt_edge > 0){
        do{
            from = randomInt(0,vert-1);
            to = randomInt(0,vert-1);
        }while(from == to || adj[from][to]);
        cnt_edge--;
        int cost = randomInt(1,MAX_COST);
        adj[from][to] = (is_weight ? cost : 1);
        if(!is_orient) adj[to][from] = (is_weight ? cost : 1);
    }
}

void Graph_matrix::add_edge(edge e){
    adj[e.from][e.to] = e.cost;
    if(!is_oriented)
        adj[e.to][e.from] = e.cost;
}

void Graph_matrix::add_edge(std::vector <edge> edges){
    for(auto e : edges)
        add_edge(e);
}


void dfs(Graph_matrix *G, int cur, std::vector <bool> &visited){
    std::cout << cur << " ";
    visited[cur] = true;
    for(int i = 0; i < G->vertices; i++)
        if(G->adj[cur][i] && !visited[i])
            dfs(G,i,visited);
}


void print_graph(Graph_matrix *G){
    std::cout << "-----------------------\n";
    for(int i = 0; i < G->vertices; i++){
        for(int j = 0; j < G->vertices; j++)
            std::cout << G->adj[i][j];
        std::cout << std::endl;
    }
    std::cout << "-----------------------\n";
}

std::vector <edge> dfs_transit(Graph_matrix *G, int st, int cur, std::vector <bool> &visited){
    visited[cur] = true;
    std::vector <edge> res;
    std::vector <edge> nw;
    if(!(st == cur || G->adj[st][cur]))
        res.push_back(edge(st,cur));
    for(int i = 0; i < G->vertices; i++){
        if(G->adj[cur][i] && !visited[i]){
            nw = dfs_transit(G,st,i,visited);
            res.insert(res.end(),nw.begin(),nw.end());
        }
    }
    return res;
}

void make_transit(Graph_matrix *G){
    std::vector <bool> visited;
    visited.resize(G->vertices,false);
    for(int i = 0; i < G->vertices; i++){
        for(int j = 0; j < G->vertices; j++) visited[j] = false;
        G->add_edge(dfs_transit(G, i, i, visited));
    }
}
void Dijkstra(Graph_matrix* G, int st){
    std::vector <bool> visited;
    int cur = st, vert = G->vertices, next = -1, d = inf;
    visited.resize(vert);
    while(true){
        visited[cur] = true;
        G->min_dist[cur][cur] = 0;
        next = -1;
        d = inf;
        for(int i = 0; i < vert; i++) {
            if(G->adj[cur][i]) {
                G->min_dist[st][i] = std::min(G->min_dist[st][i],G->adj[cur][i]+G->min_dist[st][cur]);
            }
        }
    for(int i = 0; i < vert; i++) {
        if (!visited[i] && G->min_dist[st][i] < d) {
            d = G->min_dist[st][i];
            next = i;
        }
    }
    if(next == -1)
        break;
    cur = next;
    }
}

void dfs_top(Graph_matrix *G, int cur, std::vector <bool> &visited){
    visited[cur] = true;
    int V = G->vertices;
    for(int i = 0; i < V; i++){
        if(!visited[i] && (G->adj[cur][i] != 0))
            dfs_top(G,i,visited);
    }
    G->top_sort.push_back(cur);
}


std::vector <int> topsort(Graph_matrix *G){
    int V = G->vertices;
    std::vector <bool> visited;
    visited.resize(V,false);
    for(int i = 0; i < V; i++){
        if(!visited[i]){
            dfs_top(G,i,visited);
        }
    }
    reverse (G->top_sort.begin(), G->top_sort.end());
}

void span_dfs(Graph_matrix *G, int cur, std::vector <bool> &visited){
    visited[cur] = true;
    for(int i = 0; i < G->vertices; i++)
        if(G->adj[cur][i] && !visited[i]){
            std::cout << cur << "-" << i << "\n";
            span_dfs(G,i,visited);
        }
}

void Kruskala(Graph_matrix* G){
    int V = G->vertices, m = 0;
    std::vector <std::pair <int,std::pair <int,int>>> edges (V*V); // вес - вершина 1 - вершина 2

    int cost = 0;
    std::vector <std::pair<int,int> > res;

    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if(G->adj[i][j] != 0){
                edges[m] = {G->adj[i][j],{i,j}};
                edges[m] = {G->adj[j][i],{j,i}};
                m++;
                m++;
            }
        }
    }

    std::sort (edges.begin(), edges.begin()+m);
    std::vector<int> tree_id (V);
    for(int i = 0; i < V; i++)
        tree_id[i] = i;

    int sum = 0;
    for (int i = 0; i < m; i++){
        int from = edges[i].second.first,  to = edges[i].second.second,  cost = edges[i].first;
        if (tree_id[from] != tree_id[to])
        {
            sum += cost;
            std::cout << from << "-" << to << ":" << cost << "\n";
            int old_id = tree_id[to],  new_id = tree_id[from];
            for(int j = 0; j < m; j++)
                if (tree_id[j] == old_id)
                    tree_id[j] = new_id;
        }
       }
}

