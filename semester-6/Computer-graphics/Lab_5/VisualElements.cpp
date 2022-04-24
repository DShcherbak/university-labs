#include "visualelements.h"

bool pointBelongsEdge(double x, double y, Edge edge){
    int x1 = std::min(edge.first.x, edge.second.x);
    int x2 = std::max(edge.first.x, edge.second.x);
    int y1 = std::min(edge.first.y, edge.second.y);
    int y2 = std::max(edge.first.y, edge.second.y);
    return x1 <= x && x <= x2 && y1 <= y && y <= y2;
}

bool operator >(Point a, Point b){
    if(a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
}

bool shareVertex(Edge edge1, Edge edge2){
    Point v11 = {edge1.first.x, edge1.first.y},
            v12 = {edge1.second.x, edge1.second.y},
            v21 = {edge2.first.x, edge2.first.y},
            v22 = {edge2.second.x, edge2.second.y};

    return v11 == v21 || v12 == v22 ||
            v11 == v22 || v12 == v21;
}

bool edgesIntercect(Edge edge1, Edge edge2){
    if(shareVertex(edge1, edge2)){
        return false;
    }
    double a1 = edge1.first.y - edge1.second.y;
    double b1 = edge1.second.x - edge1.first.x;
    double c1 = edge1.first.x * edge1.second.y - edge1.second.x * edge1.first.y;

    double a2 = edge2.first.y - edge2.second.y;
    double b2 = edge2.second.x - edge2.first.x;
    double c2 = edge2.first.x * edge2.second.y - edge2.second.x * edge2.first.y;

    double x0, y0;

    //horizontal
    if(a1 == 0 && a2 == 0){
        double y1 = -c1 / b1;
        double y2 = -c2 / b2;
        return y1 == y2;
    }
    if(a1 == 0){
        std::swap(a1,a2);
        std::swap(b1,b2);
        std::swap(c1,c2);
    }
    if (a2 == 0){
        y0 = -c2 / b2;
        x0 =(-c1 - b1 * y0) / a1;
        return pointBelongsEdge(x0, y0, edge1) && pointBelongsEdge(x0, y0, edge2);
    }

    //vertical

    if(b1 == 0 && b2 == 0){
        double x1 = -c1 / a1;
        double x2 = -c2 / a2;
        return x1 == x2;
    }
    if(b1 == 0){
        std::swap(a1,a2);
        std::swap(b1,b2);
        std::swap(c1,c2);
    }
    if (b2 == 0){
        x0 = -c2 / a2;
        y0 =(-c1 - a1 * x0) / b1;
        return pointBelongsEdge(x0, y0, edge1) && pointBelongsEdge(x0, y0, edge2);
    }


    //paralell
    if(a1 / a2 == b1 / b2){
        if(c2 == 0){
            return c1 == 0 && a1 == a2;
        }
        return c1 / c2 == a1 / a2;
    }

    //diagonal
    y0 = (c1 * a2 - c2 * a1) / (b2 * a1 - b1 * a2);
    x0 = (-c1 - b1 * y0) / a1;
    return pointBelongsEdge(x0, y0, edge1) && pointBelongsEdge(x0, y0, edge2);
}

bool operator ==(Point node1, Point node2){
    return node1.x == node2.x && node1.y == node2.y;
}

bool operator ==(Edge edge1, Edge edge2){
    bool result1 = (edge1.first == edge2.first && edge1.second == edge2.second);
    bool result2 = (edge1.first == edge2.second && edge1.second == edge2.first);
    return result1 || result2;
}

bool operator < (Edge e1, Edge e2){
    int x1_1 = e1.first.x, y1_1 = e1.first.y;
    int x1_2 = e1.second.x, y1_2 = e1.second.y;

    int x2_1 = e2.first.x, y2_1 = e2.first.y;
    int x2_2 = e2.second.x, y2_2 = e2.second.y;

    if(x1_1 > x1_2){
        std::swap(x1_1, x1_2);
        std::swap(y1_1, y1_2);
    }

    if(x2_1 > x2_2){
        std::swap(x2_1, x2_2);
        std::swap(y2_1, y2_2);
    }
    return x1_1 == x2_1 ? x1_2 < x2_2 : x1_1 < x2_1;
}

Chain::Chain(std::vector<std::shared_ptr<GraphicNode<int>>> nodes, int dx){
    std::sort(nodes.begin(), nodes.end(), NodeComparator);
    for(auto node : nodes){

    }
}

bool NodeComparator(std::shared_ptr<GraphicNode<int>> node1, std::shared_ptr<GraphicNode<int>> node2){
    if(node1->y == node2->y)
        return node1->x < node2->x;
    return node1->y < node2->y;
}
