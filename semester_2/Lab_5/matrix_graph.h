#include <iostream>
#include <vector>
#include <algorithm>
#pragma once
#include "bool_graph.h"

const int MAX_VERTICES = 32;
const int MAX_COST = 32;
//const double inf = 1000000000.1;


struct Graph_matrix{
    int vertices;
    int adj[MAX_VERTICES][MAX_VERTICES];
    double min_dist[MAX_VERTICES][MAX_VERTICES];
    std::vector <int> top_sort;
    bool is_oriented = false;
    bool is_weight = false;
    Graph_matrix(int vert, int cnt_edge, bool is_orient = false, bool is_wght = false);

    void add_edge(edge e);

    void add_edge(std::vector <edge> edges);
};

void make_transit(Graph_matrix &G);

void dfs(Graph_matrix *G, int cur, std::vector <bool> &visited);


void print_graph(Graph_matrix *G);

std::vector <edge> dfs_transit(Graph_matrix *G, int st, int cur, std::vector <bool> &visited);


void Dijkstra(Graph_matrix* G, int st);

void dfs_top(Graph_matrix *G, int cur, std::vector <bool> &visited);


std::vector <int> topsort(Graph_matrix *G);

void span_dfs(Graph_matrix *G, int cur, std::vector <bool> &visited);

void Kruskala(Graph_matrix* G);
