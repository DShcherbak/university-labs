#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <queue>
#include "Tree.cpp"

//const double probability = 0.1;

struct Binary_node{
    Binary_node *parent, *left, *right;
    int value;
    bool true_left_son, true_right_son;


    Binary_node(Node* a){
        value = a->value;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        true_left_son = true;
        true_right_son = true;
    }

    Binary_node(int v){
        value = v;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        true_left_son = true;
        true_right_son = true;
    }
};

void add_node(Binary_node* &root, Binary_node* new_node){
    if(root == nullptr){
        root = new_node;
        return;
    }
    if(root->value < new_node->value){
        if(root->right)
            add_node(root->right,new_node);
        else{
            root->right = new_node;
            new_node->parent = root;
        }
    }
    else{
        if(root->left)
            add_node(root->left,new_node);
        else{
            root->left = new_node;
            new_node->parent = root;
        }
    }

}

Binary_node* build_binary_tree(Node* root, Binary_node* parent = nullptr){
    if(root == nullptr)
        return nullptr;
    Binary_node* bin_root = new Binary_node(root);
    bin_root->parent = parent;
    if(root->children.size() == 0){
        return bin_root;
    }
    bin_root->left = build_binary_tree(root->children[0],bin_root);
    int n = root->children.size();
    Binary_node* father = bin_root->left;
    for(int i = 1; i < n; i++){
        father->right = build_binary_tree(root->children[i],father);
        father = father->right;
    }

    return bin_root;
}

void delete_tree(Binary_node* &root){
    if(!root)
        return;
    if(root->true_left_son)
        delete_tree(root->left);
    if(root->true_left_son)
        delete_tree(root->left);
    delete root;
}

void threaded_tree(Binary_node* &root, Binary_node* &prev){
    if(!root)
        return;
    threaded_tree(root->left,prev);
    if(prev && !(prev->right)){
        prev->right = root;
        prev->true_right_son = false;
       // std::cout << prev->value << "-R->" << (root ? root->value : -1) << "\n";
    }
    if(!root->left){
        root->left = prev;
        root->true_left_son = false;
     //  std::cout << (prev ? prev->value : -1) << "<-L-" << root->value << "\n";
    }
    prev = root;
    threaded_tree(root->right,prev);
}

Binary_node* next_threaded(Binary_node* root){
    Binary_node* next = root->right;
    if(root->true_right_son){
        while(next && next->true_left_son)
            next = next->left;
    }
    return next;
}

void print_threaded_tree(Binary_node* root){
    if(root == nullptr){
        std::cout << "Empty tree.\n";
        return;
    }
    Binary_node *cur = root, *prev = nullptr;
    while(cur->true_left_son && cur->left){
        cur = cur->left;
    }
    while(cur){
        std::cout << cur->value << " ";
        cur = next_threaded(cur);
    }
    std::cout << std::endl;
}

void print_binary_tree_right(Binary_node* root){
    std::cout << root->value << " ";
    if(root->left)
        print_binary_tree_right(root->left);
    if(root->right)
        print_binary_tree_right(root->right);
}

void print_tree_right(std::vector <Binary_node*> roots){
    int n = roots.size();
    for(int i = 0; i < n; i++){
        print_binary_tree_right(roots[i]);
    }
}

int depth(Binary_node* root){
    if(root == nullptr)
        return 0;
    if(root->left == nullptr && root->right == nullptr){
        return 1;
    }
    return 1+std::max(depth(root->left),depth(root->right));
}

void add_node_to_root(Binary_node* &root, Binary_node* son){
    son->left = nullptr;
    son->right = nullptr;
    if(!root->right){
        root->right = son;
        root->true_right_son = true;
        son->parent = root;
        return;
    }if(!root->left){
        root->left = son;
        root->true_left_son = true;
        son->parent = root;
        return;
    }
    if(randomInt(0,1))
        add_node_to_root(root->right,son);
    else
        add_node_to_root(root->left,son);
}

void add_tree_to_root(Binary_node* &root, Binary_node* son){
    if(!son)
        return;
    add_tree_to_root(root,son->left);
    add_tree_to_root(root,son->right);
    add_node_to_root(root,son);
}

void add_value_to_tree(Binary_node* &root, int v){
    Node* a = new Node(v);
    Binary_node* new_node = new Binary_node(a);
    delete(a);
    add_node(root,new_node);
}

void delete_node_by_value(Binary_node* &root, int value){
    if(!root)
        return;
    delete_node_by_value(root->left,value);
    delete_node_by_value(root->right,value);
    Binary_node* temp,*son;
    if(root->value == value){
        int new_parent = randomInt(0,1);
        if(new_parent){
            temp = root->left;
            son = root->right;
            delete root;
            root = temp;
            add_tree_to_root(root,son);
        }

    }
}


void print_tree(Binary_node *root, int depth = 0) {
    if (!root)
        return;
    std::cout << '|';
    for (int i = 0; i < depth; i++)
        std::cout << '\t' << '|';
    std::cout << root->value << std::endl;
    print_tree(root->left, depth + 1);
    for (int i = 0; i < depth; i++)
        std::cout << '\t' << '|';
    std::cout << "---\n";
    print_tree(root->right, depth + 1);
}
