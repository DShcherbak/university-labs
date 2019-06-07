#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>
#include "bool_graph.h"

int randomInteger(int begin, int end) {
    static std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

Graph_bool::Graph_bool(int vert, int cnt_edge, bool is_orient){
    int from;
    int to;
    vertices = vert;
    for(int i : adj) i = 0;
    for(int i = 0; i < vertices; i++)
        for(int j = 0; j < vertices; j++)
            min_dist[i][j] = inf;
        while(cnt_edge > 0){
            do{
                from = randomInteger(0,vert-1);
                to = randomInteger(0,vert-1);
            //    std::cout <<edge <<" " <<  from <<" " << to << std::endl;
            //    std::cin >> to;
            //    std::cout << adj[from] <<" & " << (1<<to) << "\n";
            }while(from == to || adj[from]&(1<<to));
            cnt_edge--;
            adj[from] |= (1<<to);
            if(!is_orient) adj[to] |= (1 << from);
        }
}

void Graph_bool::add_edge(edge e){     // std::cout << "new:" << e.from << " => " << e.to << "\n";
    adj[e.from] |= (1<<e.to);
    if(!is_oriented)
        adj[e.to] |= (1<<e.from);
}

void Graph_bool::add_edge(std::vector <edge> edges){
        for(auto e : edges)
            add_edge(e);
}


void dfs(Graph_bool *G, int cur, std::vector <bool> &visited){
    std::cout << cur << " ";
    visited[cur] = true;
    for(int i = 0; i < G->vertices; i++)
        if((G->adj[cur]&(1<<i)) && !visited[i])
            dfs(G,i,visited);
}

void print_graph(Graph_bool *G){
    int temp;
    std::cout << "-----------------------\n";
    for(int i = 0; i < G->vertices; i++){
        temp = G->adj[i];
        for(int j = 0; j < G->vertices; j++) {
            std::cout << temp%2;
            temp = temp>>1;
        }
        std::cout << "\n";
    }
    std::cout << "-----------------------\n";
}

std::vector <edge> dfs_transit(Graph_bool *G, int st, int cur, std::vector <bool> &visited){
    visited[cur] = true;
    std::vector <edge> res;
    std::vector <edge> nw;
    if(!(st == cur || (G->adj[st]&(1<<cur))))
        res.push_back(edge(st,cur));
    for(int i = 0; i < G->vertices; i++){
        if( (G->adj[cur]&(1<<i)) && !visited[i]){
            //print_graph(G);
            nw = dfs_transit(G,st,i,visited);
            res.insert(res.end(),nw.begin(),nw.end());
        }
    }
    return res;
}
void make_transit(Graph_bool *G){
    std::vector <bool> visited;
    visited.resize(G->vertices,false);
    for(int i = 0; i < G->vertices; i++){
        for(int j = 0; j < G->vertices; j++) visited[j] = false;
        G->add_edge(dfs_transit(G, i, i, visited));
    }
}

void Dijkstra(Graph_bool* G, int st){
    std::vector <bool> visited;
    int cur = st, vert = G->vertices, next = -1, d = inf;
    visited.resize(vert);
    while(true){
        visited[cur] = true;
        G->min_dist[cur][cur] = 0;
        next = -1;
        d = inf;
        for(int i = 0; i < vert; i++) {
            if(G->adj[cur]&(1<<i)) {
                G->min_dist[st][i] = std::min(G->min_dist[st][i],1+G->min_dist[st][cur]);
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

void dfs_top(Graph_bool *G, int cur, std::vector <bool> &visited){
    visited[cur] = true;
    int V = G->vertices;
    for(int i = 0; i < V; i++){
        if(!visited[i] && (G->adj[cur] & (1 << i)))
            dfs_top(G,i,visited);
    }
    G->top_sort.push_back(cur);
}


std::vector <int> topsort(Graph_bool *G){
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

void span_dfs(Graph_bool *G, int cur, std::vector <bool> &visited){
    visited[cur] = true;
    for(int i = 0; i < G->vertices; i++)
        if((G->adj[cur]&(1<<i)) && !visited[i]){
            std::cout << cur << "-" << i << "\n";
            dfs(G,i,visited);
        }
}
/*
void Kruskala(Graph_bool* G){
    int V = G->vertices, M;
    std::vector <edge*> edges; // вес - вершина 1 - вершина 2

    int cost = 0;
    std::vector <std::pair<int,int> > res;

    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if(G->adj[i]&(1<<j)){
                edges.push_back(new edge(i,j,G->adj[i][j]));
                M++;
            }
        }
    }
    sort (edges.begin(), edges.end());
    std::vector<int> tree_id (V);
    for(int i = 0; i < V; i++)
        tree_id[i] = i;

    int sum = 0;
    for (int i = 0; i < V-1; i++){
        int from = edges[i]->from,  to = edges[i]->to,  cost = edges[i]->weight;
        if (tree_id[from] != tree_id[to])
        {
            sum += cost;
            std::cout << from << "-" << to << "\n";
            int old_id = tree_id[to],  new_id = tree_id[from];
            for(int j = 0; j < M; j++)
                if (tree_id[j] == old_id)
                    tree_id[j] = new_id;
        }
    }
}
*/