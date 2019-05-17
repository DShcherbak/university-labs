//
// Created by sadoffnick on 16.05.19.
//

#include <random>

const int MAX_VERTICES = 32;
const int MAX_COST = 32;



int randomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);

}

struct edge{
    int from;
    int to;
    int weight = 1;

    edge(int f, int t, int w = 1){
        from = f;
        to  = t;
        weight = w;
    }
};

struct Graph_matrix{
    int vertices;
    int adj[MAX_VERTICES][MAX_VERTICES];
    bool is_oriented = false;
    bool is_weight = false;


    Graph_matrix(int vert, int edge, bool is_orient = false, bool is_wght = false){
        int from;
        int to;
        vertices = vert;
        is_oriented = is_orient;
        is_weight = is_wght;
        while(edge > 0){
            do{
                from = randomInt(0,vert-1);
                to = randomInt(0,vert-1);
            }while(from == to || adj[from][to]);
            edge--;
            int cost = randomInt(1,MAX_COST);
            adj[from][to] = (is_weight ? cost : 1);
            if(!is_orient) adj[to][from] = (is_weight ? cost : 1);
        }
    }

    void add_edge(edge e){
        adj[e.from][e.to] = e.weight;
        if(!is_oriented)
            adj[e.to][e.from] = e.weight;
    }

    void add_edge(std::vector <edge> edges){
        for(auto e : edges)
            add_edge(e);
    }

};

void dfs(Graph_matrix G, int cur, std::vector <bool> &visited){
    std::cout << cur << " ";
    visited[cur] = true;
    for(int i = 0; i < G.vertices; i++)
        if(G.adj[cur][i] && !visited[i])
            dfs(G,i,visited);
}


void print_graph(Graph_matrix G){
    std::cout << "-----------------------\n";
    for(int i = 0; i < G.vertices; i++){
        for(int j = 0; j < G.vertices; j++)
            std::cout << G.adj[i][j];
        std::cout << std::endl;
    }
    std::cout << "-----------------------\n";
}

std::vector <edge> dfs_transit(Graph_matrix G, int st, int cur, std::vector <bool> &visited){
    visited[cur] = true;
    std::vector <edge> res;
    std::vector <edge> nw;
    if(!(st == cur || G.adj[st][cur]))
        res.push_back(edge(st,cur));
    for(int i = 0; i < G.vertices; i++){
        if(G.adj[cur][i] && !visited[i]){
            nw = dfs_transit(G,st,i,visited);
            res.insert(res.end(),nw.begin(),nw.end());
        }
    }
    return res;
}

void make_transit(Graph_matrix &G){
    std::vector <bool> visited;
    visited.resize(G.vertices,false);
    for(int i = 0; i < G.vertices; i++){
        for(int j = 0; j < G.vertices; j++) visited[j] = false;
        G.add_edge(dfs_transit(G, i, i, visited));
    }
}
