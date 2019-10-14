//
// Created by sadoffnick on 11.10.19.
//

#ifndef LAB_1_BINARY_NODE_H
#define LAB_1_BINARY_NODE_H

template <class T>
class binary_node {

private:
    T value;
    binary_node<T>* parent;
public:
    binary_node<T>* left;
    binary_node<T>* right;

    explicit binary_node<T>(T value);

    T get_value();

    void set_parent(binary_node<T>* new_parent);

    void add_son(binary_node<T>* new_son);

    void delete_son(T val);

    void delete_son_by_id(int id);

    binary_node* search_for_value_dfs(T val);

    binary_node* search_for_value_bfs(T val);

};

#include "../includes/binary_node.inc"


#endif //LAB_1_BINARY_NODE_H
