#ifndef LAB_1_TREE_NODE_H
#define LAB_1_TREE_NODE_H

#include <vector>
template <class T>
class tree_node {
private:
    T value;
    tree_node<T>* parent;
    std::vector <tree_node<T>*> children;
public:

    tree_node<T>(T value);

    T get_value();

    void set_parent(tree_node<T>* new_parent);

    void add_son(tree_node<T>* new_son);

    void delete_son(T val);

    void delete_son_by_id(int num);

    tree_node* search_for_value_dfs(T val);

    tree_node* search_for_value_bfs(T val);

};

#include "tree_node.inc"

#endif //LAB_1_TREE_NODE_H
