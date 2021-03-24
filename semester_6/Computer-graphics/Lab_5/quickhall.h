#ifndef QUICKHALL_H
#define QUICKHALL_H
#include <vector>
#include <memory>
#include "visualelements.h"

#define GNode std::shared_ptr<GraphicNode<int>>

std::vector<std::vector<std::shared_ptr<Edge>>> QuickHull(std::vector<GNode> nodes, GNode left, GNode right, int side);

#endif // QUICKHALL_H
