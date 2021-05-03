#ifndef JARVICE_H
#define JARVICE_H
#include <vector>
#include <memory>
#include "visualelements.h"

#define GNode std::shared_ptr<GraphicNode<int>>

std::vector<std::vector<std::shared_ptr<Edge>>> Jarvice(std::vector<GNode> nodes);

std::vector<std::vector<std::shared_ptr<Edge>>> DivideAndConquere(std::vector<GNode> nodes);

#endif // JARVICE_H
