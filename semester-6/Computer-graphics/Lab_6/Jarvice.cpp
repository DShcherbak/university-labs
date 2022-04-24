#include "Jarvice.h"

int distanceToLine(GNode left, GNode right, GNode p)
{
    return abs ((p->y - left->y) * (right->x - left->x) -
               (right->y - left->y) * (p->x - left->x));
}

int findSide(GNode left, GNode right, GNode p)
{
    int val = (p->y - right->y) * (right->x - left->x) - (right->y - left->y) * (p->x - right->x);

    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

int min_ind(std::vector<GNode> points){
    int result = 0;
    for(int i = 1; i < (int) points.size(); i++){
            if(points[i]->x < points[result]->x){
                result = i;
            } else if (points[i]->x == points[result]->x){
                if(points[i]->y > points[result]->y){
                    result = i;
                }
            }
    }
    return result;
}

bool less(GNode a, GNode b){
    if(a->x == b->x){
        return a->y < b->y;
    } else {
        return a->x < b->x;
    }
}

std::vector<std::shared_ptr<Edge>> combine(std::vector<std::shared_ptr<Edge>> two_hulls){
    std::vector<GNode> nodes;
    for(auto edge : two_hulls){
        nodes.emplace_back(std::make_shared<GraphicNode<int>>(edge->first.x, edge->first.y, Qt::black, 0));
    }
    auto jar = Jarvice(nodes);
    return jar[jar.size()-1];
}

std::vector<std::vector<std::shared_ptr<Edge>>> DivideAndConquere(std::vector<GNode> nodes){
    const int threshold = 10;
    if(nodes.size() > threshold){
        std::sort(nodes.begin(), nodes.end(), less);
        int mid = nodes.size() >> 1;
        std::vector<GNode> left_array;
        std::vector<GNode> right_array;
        for(int i = 0; i < (int) nodes.size(); i++){
            if(i <= mid){
                left_array.push_back(nodes[i]);
            } else {
                right_array.push_back(nodes[i]);
            }
        }
        auto left_result = DivideAndConquere(left_array);
        auto right_result = DivideAndConquere(right_array);
        auto left_final = left_result[left_result.size()-1];
        for(int i = 0; i < (int) right_result.size(); i++){
            right_result[i].insert(right_result[i].end(), left_final.begin(), left_final.end());
        }
        left_result.insert(left_result.end(), right_result.begin(), right_result.end());
        left_result.push_back(combine(right_result[right_result.size()-1]));
        return left_result;
    } else {
        return Jarvice(nodes);
    }
    return {};
}

std::vector<std::vector<std::shared_ptr<Edge>>> Jarvice(std::vector<GNode> nodes){
    std::vector<std::vector<std::shared_ptr<Edge>>> result;
    std::vector<std::shared_ptr<Edge>> result_iteration;
    std::vector<GNode> hull;
    int n = nodes.size();
    if(n < 3)
        return {};
    int l = min_ind(nodes);
    int p = l;
    while(true){
        hull.push_back(nodes[p]);
        int q = (p + 1) % n;
        for(int i = 0; i < n; i++){
            if(findSide(nodes[p], nodes[i], nodes[q]) == 1){
                q = i;
            }
        }
        p = q;
        if(p == l)
            break;
    }
    n = hull.size();
    for(int i = 0; i < n-1; i++){
        result_iteration.emplace_back(std::make_shared<Edge>(hull[i], hull[i+1]));
        result.push_back(result_iteration);
    }
    result_iteration.emplace_back(std::make_shared<Edge>(hull[n-1],hull[0]));
    result.push_back(result_iteration);
    return result;
}
