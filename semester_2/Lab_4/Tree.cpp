#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <queue>

const double probability = 0.1;

int randomInt(int begin, int end){
    static std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

struct Node {
    Node *parent;
    int value;
    std::vector <Node*> children;

    Node(int v){
        value = v;
    }
};

void add_node_to_root(Node* &root, Node* &new_node, double proh) {
    if(root == nullptr){
        root = new_node;
        std::cout << new_node->value << " ? " << root->value << "\n";
        return;
    }
    double d = randomInt(0, 100) * 0.01;
    int id;
    if (d < proh || root->children.size() == 0) {
        root->children.push_back(new_node);
        new_node->parent = root;
    } else {
        id = randomInt(0, root->children.size()-1);
        add_node_to_root(root->children[id], new_node, proh);
    }
}

Node* build_tree(){
    return nullptr;
}

void add_value_to_tree(Node* &root, int v){
    Node* new_node = new Node(v);
    add_node_to_root(root,new_node,probability);
}

void print_node_right(Node* root){
    for(auto ch:root->children)
        print_node_right(ch);
}

void print_tree_right(std::vector <Node*> roots){
    int n = roots.size();
    for(int i = 0; i < n; i++){
        print_node_right(roots[i]);
    }
}

void print_tree(Node *root, int depth = 0) {
    if (!root){
        std::cout << "Empty tree.";
        return;
    }
    std::cout << '|';
    for (int i = 0; i < depth; i++)
        std::cout << '\t' << '|';
    std::cout << root->value << "\n";
    for(auto ch : root->children)
        print_tree(ch,depth+1);
}

void delete_node_by_value(Node* &root, int value){
    if(!root)
        return;
    for(auto ch:root->children)
        delete_node_by_value(ch,value);
    if(root->value == value){
        int new_parent = randomInt(0, root->children.size()-1);
        for(int i = 0; i < root->children.size(); i++){
            if(i == new_parent)
                continue;
            root->children[i]->parent = root->children[new_parent];
            root->children[new_parent]->children.push_back(root->children[i]);
        }
        Node* temp = root->children[new_parent];
        delete root;
        root = temp;
    }
}

