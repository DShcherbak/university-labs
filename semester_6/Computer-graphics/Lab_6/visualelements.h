#ifndef VISUALELEMENTS_H
#define VISUALELEMENTS_H
#include <QPainter>
#include <memory>

struct Point{
    int x, y;

    Point() = default;

    Point(int _x, int _y){
        x = _x;
        y = _y;
    }
};

bool operator >(Point a, Point b);

template <class T>
struct GraphicNode{
    T value;
    int x, y;
    Qt::GlobalColor nodeColor = Qt::white;
    bool selected = false;

    GraphicNode(T val){
        x = 0;
        y = 0;
        nodeColor = Qt::white;
        value = val;
    }

    GraphicNode(int _x, int _y, Qt::GlobalColor cl, T val){
        x = _x;
        y = _y;
        nodeColor = cl;
        value = val;
    }


};

bool NodeComparator(std::shared_ptr<GraphicNode<int>> node1, std::shared_ptr<GraphicNode<int>> node2);



struct Edge{
    Point first, second;
    Qt::GlobalColor color = Qt::black;

    Edge() = default;

    Edge(const Point& _first, const Point& _second){
        first  = Point(_first.x, _first.y);
        second = Point(_second.x, _second.y);
    }

    Edge(int x1, int y1, int x2, int y2){
        first  = Point(x1, y1);
        second = Point(x2, y2);
    }

    Edge(int x1, int y1, int x2, int y2, Qt::GlobalColor color){
        first  = Point(x1, y1);
        second = Point(x2, y2);
        this->color = color;
    }

    Edge(std::shared_ptr<GraphicNode<int>> _first, std::shared_ptr<GraphicNode<int>> _second){
        first  = Point(_first->x, _first->y);
        second = Point(_second->x, _second->y);
    }
};

struct Chain{
    Chain(std::vector<std::shared_ptr<GraphicNode<int>>> nodes, int dx);
    std::vector<std::shared_ptr<Edge>> edges;
};

bool operator < (Edge e1, Edge e2);

bool edgesIntercect(Edge e1, Edge e2);

bool operator ==(Point node1, Point node2);

bool operator ==(Edge edge1, Edge edge2);



#endif // VISUALELEMENTS_H
