
#pragma once
//#include "matrix_graph.h"

const double inf = 100000000.1;

struct edge{
    int from;
    int to;
    int cost;

    edge(int f, int t, int c = 1);
};



const int Nmax = 32;

struct Graph_bool {
    int vertices; // ALWAYS LESS THAN 32
    int adj[Nmax];
    double min_dist[Nmax][Nmax];
    std::vector<int> top_sort;
    bool is_oriented = false;

    Graph_bool(int vert, int cnt_edge, bool is_orient = false);

    void add_edge(edge e);

    void add_edge(std::vector<edge> edges);
};


void dfs(Graph_bool *G, int cur, std::vector <bool> &visited);

void print_graph(Graph_bool *G);

std::vector <edge> dfs_transit(Graph_bool *G, int st, int cur, std::vector <bool> &visited);


void Dijkstra(Graph_bool* G, int st);

void dfs_top(Graph_bool *G, int cur, std::vector <bool> &visited);


std::vector <int> topsort(Graph_bool *G);

void span_dfs(Graph_bool *G, int cur, std::vector <bool> &visited);
void Kruskala(Graph_bool* G);