#ifndef LAB_1_TREE_NODE_H
#define LAB_1_TREE_NODE_H

#include <vector>

template <class T>
class tree_node {
    T value;
    tree_node<T>* parent;
    std::vector <tree_node<T>*> children;

    void set_parent(tree_node<T>* new_parent);

    void add_son(tree_node<T>* new_son);

    void delete_son(T val);

    void delete_son(int num);

    tree_node* search_for_value(T val);
};


#endif //LAB_1_TREE_NODE_H
