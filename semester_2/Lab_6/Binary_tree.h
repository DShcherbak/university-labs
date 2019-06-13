#ifndef LAB_6_BINARY_TREE_H
#define LAB_6_BINARY_TREE_H

struct Node;

class Binary_tree {
public:
    Node *root;

    Binary_tree *create_empty();

    void add_element(int value);

    void add_node(Node *node);

    void delete_element(int value);

    int find_by_range(int st, int fin);

    void print();
};

#endif //LAB_6_BINARY_TREE_H
