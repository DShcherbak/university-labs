#ifndef LAB_1_TREE_NODE_H
#define LAB_1_TREE_NODE_H

#include <vector>
#include <string>
template <class T>
class tree_node {
private:
    T value;
    tree_node<T>* parent;
public:
    std::vector <tree_node<T>*> children;

    explicit tree_node<T>(T value);

    T get_value();

    tree_node<T>* get_parent();

    void set_parent(tree_node<T>* new_parent);

    void add_son(tree_node<T>* new_son);

    void delete_son(T val, bool _r);

    void delete_son_by_id(int id, bool _r);

    tree_node* search_for_value_dfs(T val);

    tree_node* search_for_value_bfs(T val);

};


#include "../includes/tree_node.inc"

#endif //LAB_1_TREE_NODE_H
