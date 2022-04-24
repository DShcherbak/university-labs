#ifndef HULLTREE_H
#define HULLTREE_H

#include <memory>
#include <iostream>
#include "visualelements.h"

struct HullNode;

struct HullEdge{
    std::shared_ptr<HullNode> start;
    std::shared_ptr<HullNode> end;
};

struct HullNode{
    int x, y;
    bool part = false;
    std::shared_ptr<HullNode> left, right, parent;
    std::vector<std::shared_ptr<HullEdge>> edges;
};

class HullTree {
private:
    bool upperTree;

    std::vector<GraphicNode<int>> vertices;
    std::vector<HullNode> nodes;
    std::vector<HullEdge> edges;

public:
    std::shared_ptr<HullNode> root;
    HullTree();
    HullTree(bool up = true);
    std::vector<std::shared_ptr<Edge>> getHull();
    bool hasNode(int x, int y);
    std::shared_ptr<HullNode> fixTree(std::shared_ptr<HullNode> node);
    std::shared_ptr<HullNode> addNode(int x, int y);
    std::shared_ptr<HullNode> eraseNode(int x, int y);
    void printTree();
    void reset();
};

#endif // HULLTREE_H

