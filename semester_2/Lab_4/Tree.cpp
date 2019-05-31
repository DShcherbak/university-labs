#include <random>
#include <algorithm>
#include <queue>

const double probability = 0.1;

int randomInt(int begin, int end) {
    static std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}


struct Binary_node{
    Binary_node* parent;
    int value;
    Binary_node *left, *right;

    Binary_node(Node* a){
        value = a->value;
    }
};

void add_node_to_root(Node* root, Node* new_node, double proh) {
    if(root == nullptr){
        root = new_node;
        return;
    }
    double d = randomInt(0, 100) * 0.01;
    int id;
    if (d < proh || root->children.size() == 0) {
        root->children.push_back(new_node);
        new_node->parent = root;
    } else {
        id = randomInt(0, root->children.size());
        add_node_to_root(root->children[id], new_node, proh);
    }
}

Node* build_tree(){
    return nullptr;
}

void add_value_to_tree(Node* root, int v){
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

void print_tree(Node *root,int type = 0,  int depth = 0) {
    if (!root)
        return;
    std::cout << '|';
    for (int i = 0; i < depth; i++)
        std::cout << '\t' << '|';
    std::cout << root->value;
    for(auto ch : root->children)
        print_tree(ch,type,depth+1);
}

void delete_node_by_value(Node* root, Node* cur, int value){
    if(root->value == value){
        Node* new_root = build_tree();
    }

}

