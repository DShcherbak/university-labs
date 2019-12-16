#ifndef LAB_1_TREE_NODE_H
#define LAB_1_TREE_NODE_H

#include <vector>
#include <string>
template <class T>
class tree_node {
private:
    T* value;
    tree_node<T>* parent;
    std::string path;
    int id;
    int level;
public:

    std::vector <tree_node<T>*> children;

    explicit tree_node<T>(T* value, int _id, int _level);

    T* get_value();
    tree_node<T>* get_parent();
    std::string get_path();
    int get_id();
    int get_level();

    void set_parent(tree_node<T>* new_parent);
    void set_path(std::string _path);
    void add_son(tree_node<T>* new_son);

    void delete_son(T val, bool _r);
    void delete_son_by_id(int id, bool _r);

    tree_node* search_for_value_dfs(std::string val);
    tree_node* search_for_value_bfs(std::string val);

    void print_tree(int depth = 0);
};


#include "../includes/tree_node.inc"

#endif //LAB_1_TREE_NODE_H
