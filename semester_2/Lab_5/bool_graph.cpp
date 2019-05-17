//
// Created by sadoffnick on 16.05.19.
//

struct Graph_bool{
    int vertices; // ALWAYS LESS THAN 32
    int adj[32];
    bool is_oriented = false;

    Graph_bool(int vert, int edge, bool is_orient = false){
        int from;
        int to;
        vertices = vert;
        for(int i : adj) i = 0;
        while(edge > 0){
            do{
                from = randomInt(0,vert-1);
                to = randomInt(0,vert-1);
            //    std::cout <<edge <<" " <<  from <<" " << to << std::endl;
            //    std::cin >> to;
            //    std::cout << adj[from] <<" & " << (1<<to) << "\n";
            }while(from == to || adj[from]&(1<<to));
            edge--;
            int cost = randomInt(1,MAX_COST);
            adj[from] |= (1<<to);
            if(!is_orient) adj[to] |= (1 << from);
        }
    }

    void add_edge(edge e){
        // std::cout << "new:" << e.from << " => " << e.to << "\n";
        adj[e.from] |= (1<<e.to);
        // std::cout << adj[e.from][e.to] << "\n";
        if(!is_oriented)
            adj[e.to] |= (1<<e.from);
    }

    void add_edge(std::vector <edge> edges){
        for(auto e : edges)
            add_edge(e);
    }

};

void dfs(Graph_bool G, int cur, std::vector <bool> &visited){
    std::cout << cur << " ";
    visited[cur] = true;
    for(int i = 0; i < G.vertices; i++)
        if((G.adj[cur]&(1<<i)) && !visited[i])
            dfs(G,i,visited);
}

void print_graph(Graph_bool G){
    int temp;
    std::cout << "-----------------------\n";
    for(int i = 0; i < G.vertices; i++){
        temp = G.adj[i];
        for(int j = 0; j < G.vertices; j++) {
            std::cout << temp%2;
            temp = temp>>1;
        }
        std::cout << "\n";
    }
    std::cout << "-----------------------\n";
}

std::vector <edge> dfs_transit(Graph_bool G, int st, int cur, std::vector <bool> &visited){
    visited[cur] = true;
    std::vector <edge> res;
    std::vector <edge> nw;
    if(!(st == cur || (G.adj[st]&(1<<cur))))
        res.push_back(edge(st,cur));
    for(int i = 0; i < G.vertices; i++){
        if( (G.adj[cur]&(1<<i)) && !visited[i]){
            //print_graph(G);
            nw = dfs_transit(G,st,i,visited);
            res.insert(res.end(),nw.begin(),nw.end());
        }
    }
    return res;
}
void make_transit(Graph_bool &G){
    std::vector <bool> visited;
    visited.resize(G.vertices,false);
    for(int i = 0; i < G.vertices; i++){
        for(int j = 0; j < G.vertices; j++) visited[j] = false;
        G.add_edge(dfs_transit(G, i, i, visited));
    }
}
