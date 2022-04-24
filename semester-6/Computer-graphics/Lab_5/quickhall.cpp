#include "quickhall.h"

int distanceToLine(GNode left, GNode right, GNode p)
{
    return abs ((p->y - left->y) * (right->x - left->x) -
               (right->y - left->y) * (p->x - left->x));
}

int findSide(GNode left, GNode right, GNode p)
{
    int val = (p->y - left->y) * (right->x - left->x) - (right->y - left->y) * (p->x - left->x);

    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

std::vector<std::vector<std::shared_ptr<Edge>>> QuickHull(std::vector<GNode> GNodes, GNode left, GNode right, int side){
    std::vector<std::vector<std::shared_ptr<Edge>>> result;

    int ind = -1;
    int maxDist = 0;
    int n = GNodes.size();
    for (int i=0; i<n; i++)
    {
        int currentDist = distanceToLine(left, right, GNodes[i]);
        if (findSide(left, right, GNodes[i]) == side && currentDist > maxDist)
        {
            ind = i;
            maxDist = currentDist;
        }
    }
    if (ind == -1)
    {
        std::vector<std::shared_ptr<Edge>> newEdge;
        newEdge.push_back(std::make_shared<Edge>(left->x, left->y, right->x, right->y, Qt::black));
        //add edge to canvas
        result.push_back(newEdge);
        return result;
    }

    std::vector<std::shared_ptr<Edge>> tempEdges;
    //add temporary edges to canvas
    tempEdges.push_back(std::make_shared<Edge>(GNodes[ind]->x, GNodes[ind]->y, left->x, left->y, Qt::red));
    tempEdges.push_back(std::make_shared<Edge>(GNodes[ind]->x, GNodes[ind]->y, right->x, right->y, Qt::red));
    result.push_back(tempEdges);

    //recursive call of QUickHull
    auto r1 = QuickHull(GNodes, GNodes[ind], left, -findSide(GNodes[ind], left, right));
    result.insert(result.end(), r1.begin(), r1.end());
    r1 = QuickHull(GNodes, GNodes[ind], right, -findSide(GNodes[ind], right, left));
    result.insert(result.end(), r1.begin(), r1.end());
    return result;
}
