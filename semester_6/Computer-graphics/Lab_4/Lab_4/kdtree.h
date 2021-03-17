#ifndef KDTREE_H
#define KDTREE_H

#include <vector>
#include <memory>
#include "visualelements.h"

struct KDNode{
    int number;
    bool vertical = true;
    int value;
    int additionalValue;
    std::shared_ptr<KDNode> left = nullptr;
    std::shared_ptr<KDNode> right = nullptr;
};


class KdTree
{
    std::shared_ptr<KDNode> root;

public:
    std::vector<std::shared_ptr<Edge>> lines;
    KdTree(std::vector<std::shared_ptr<GraphicNode<int>>> nodes);
    std::vector<std::shared_ptr<GraphicNode<int>>> checkArea(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2);

private:
    std::shared_ptr<KDNode> build_vertical(std::vector<std::shared_ptr<GraphicNode<int>>> nodes, int l, int r);
    std::shared_ptr<KDNode> build_horizontal(std::vector<std::shared_ptr<GraphicNode<int>>> nodes, int l, int r);
};

#endif // KDTREE_H
