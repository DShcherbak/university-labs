#include "kdtree.h"

#define nodeV std::vector<std::shared_ptr<GraphicNode<int>>>
#define Nmax 1000

std::shared_ptr<KDNode> KdTree::build_horizontal(nodeV nodes, int l, int r){ 
    if(l > r)
        return nullptr;
    if(r - l == 0){
        auto result = std::make_shared<KDNode>();
        result->number = l;
        result->vertical = false;
        int y = nodes[l]->y;
        lines.push_back(std::make_shared<Edge>(-100, y, +1800, y, Qt::lightGray));
        result->value = y;
        result->additionalValue = nodes[l]->x;
        return result;
    }
    std::sort(nodes.begin() + l, nodes.begin() + r, [](std::shared_ptr<GraphicNode<int>> a, std::shared_ptr<GraphicNode<int>> b)
    {
        return a->y < b->y;
    });
    int m = (l + r) >> 1;
    auto middle = nodes[m];
    auto result = std::make_shared<KDNode>();
    result->number = m;
    result->vertical = false;
    int y = middle->y;
    result->value = y;
    lines.push_back(std::make_shared<Edge>(-100, y, +1800, y, Qt::lightGray));
    result->additionalValue = middle->x;

    std::vector<std::shared_ptr<GraphicNode<int>>> leftVector;
    leftVector.insert(leftVector.end(), nodes.begin(), nodes.begin() + m);
    std::vector<std::shared_ptr<GraphicNode<int>>> rightVector;
    rightVector.insert(rightVector.end(), nodes.begin() + m + 1, nodes.end());
    result->left = build_vertical(leftVector, 0, m - 1);
    result->right = build_vertical(rightVector, 0, r - m - 1);
    return result;
}

std::shared_ptr<KDNode> KdTree::build_vertical(nodeV nodes, int l, int r){
    if(l > r)
        return nullptr;
    if(r - l == 0){
        auto result = std::make_shared<KDNode>();
        result->number = l;
        int x = nodes[l]->x;
        result->value = x;
        lines.push_back(std::make_shared<Edge>(x, -100, x, +800, Qt::lightGray));
        result->additionalValue = nodes[l]->y;
        return result;
    }
    std::sort(nodes.begin() + l, nodes.begin() + r, [](std::shared_ptr<GraphicNode<int>> a, std::shared_ptr<GraphicNode<int>> b)
    {
        return a->x < b->x;
    });
    int m = (l + r) >> 1;
    auto middle = nodes[m];
    auto result = std::make_shared<KDNode>();
    result->number = m;
    int x = middle->x;
    result->value = x;
    lines.push_back(std::make_shared<Edge>(x, -100, x, +800, Qt::lightGray));
    result->additionalValue = middle->y;
    std::vector<std::shared_ptr<GraphicNode<int>>> leftVector;
    leftVector.insert(leftVector.end(), nodes.begin(), nodes.begin() + m);
    std::vector<std::shared_ptr<GraphicNode<int>>> rightVector;
    rightVector.insert(rightVector.end(), nodes.begin() + m + 1, nodes.end());
    result->left = build_horizontal(leftVector, 0, m - 1);
    result->right = build_horizontal(rightVector, 0, r - m - 1);
    return result;
}

KdTree::KdTree(nodeV nodes){
    root = build_vertical(nodes, 0, nodes.size() - 1);
}

nodeV checkNodeArea(std::shared_ptr<KDNode> node, std::shared_ptr<Point> p1, std::shared_ptr<Point>p2){
    int l, r, la, ra;
    nodeV result;
    l = p1->x, r = p2->x;
    la = p1->y, ra = p2->y;

    if(!node->vertical){
        std::swap(l, la);
        std::swap(r, ra);
    }

    if(l <= node->value && node->value <= r){
        if(la <= node->additionalValue &&
                node->additionalValue <= ra){
            if(node->vertical)
                result.push_back(std::make_shared<GraphicNode<int>>(node->value, node->additionalValue, Qt::red, 0));
            else
                result.push_back(std::make_shared<GraphicNode<int>>(node->additionalValue, node->value, Qt::red, 0));
        }
    }
    if(node->left != nullptr && l < node->value){
        auto newVerts = checkNodeArea(node->left, p1, p2);
        result.insert(result.end(), newVerts.begin(), newVerts.end());
    }
    if(node->right != nullptr && node->value < r){
        auto newVerts = checkNodeArea(node->right, p1, p2);
        result.insert(result.end(), newVerts.begin(), newVerts.end());
    }
    return result;
}

nodeV KdTree::checkArea(std::shared_ptr<Point> p1, std::shared_ptr<Point>p2){
    if(p1->x > p2->x){
        std::swap(p1, p2);
    }
    if(p1->y > p2->y){
        std::swap(p1->y, p2->y);
    }
    return checkNodeArea(root, p1, p2);
}
