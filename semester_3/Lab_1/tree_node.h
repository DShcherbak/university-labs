#ifndef LAB_1_TREE_NODE_H
#define LAB_1_TREE_NODE_H

#include <vector>

using namespace std;

template <class T>
class tree_node {
    T value;
    tree_node* parent;
    vector <tree_node*> children;

    void add_son(T new_son);

    void delete_son();
};


#endif //LAB_1_TREE_NODE_H
