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


Binary_node* build_binary_tree(Node* root, Binary_node* parent){
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
        father->right = build_binary_tre

                e(root->children[i],father);
        father = father->right;
    }

    return bin_root;
}

void sewd_tree(Binary_node* &root){
    if(!root)
        return;
    Binary_node* prev = nullptr;
    sewd_tree(root->left);
    if(prev && !(prev->true_right_son))
        prev->right = root;
    if(!root->left)
        root->left = prev;
    prev = root;
    sewd_tree(root->right);
}

Binary_node* next_sewd(Binary_node* root){
    Binary_node* next = root->right;
    if(root->true_right_son){
        while(next->true_left_son)
            next = next->left;
    }
    return next;
}

void print_sewd_tree(Binary_node* root){
    Binary_node *cur = root, *prev = nullptr;
    while(cur->true_left_son)
        cur = cur->left;
    while(cur){
        std::cout << cur->value << " ";
        cur = next_sewd(cur);
    }
    std::cout << std::endl;
}

/*
Binary_node* build__binary_tree(std::vector <Application*> apps, std::vector <edge> valueances){
    int n = valueances.size();
    random_shuffle(valueances);
    edge p = valueances[0];
    Binary_node* root = new Binary_node(apps[p.from],apps[p.to],p.cost);
    for(int i = 1; i <n; i++){
        p = valueances[i];
        Binary_node* new_node = new Binary_node(apps[p.from],apps[p.to],p.cost);
        add_node(root,new_node);
    }
    return root;

}

int create_new_node(std::vector <Binary_node*> root, Application* a, Application* b){
    Binary_node* new_node = new Binary_node(a,b,valueance(a,b));
    if(randomInt(1,1000)*0.1/100.0 < probability)
        root.push_back(new_node);
    else{
        int par = randomInt(0,root.size()-1);
        add_node(root[par],new_node);
    }
}

 */
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

void delete_node_by_value(Binary_node* root, int val){
    if(root->value == val){
        if(root->parent == nullptr) {
            root->right->parent = root->left;
        }
    }
}

void delete_root_by_value(Binary_node* root, int val){
    if(root->value == val){
        //delete
    }
    else if(root->value < val)
        delete_node_by_value(root->left,val);
    else
        delete_node_by_value(root->right,val);
}


void print_tree(Binary_node *root, int depth = 0) {
    if (!root)
        return;
    std::cout << '|';
    for (int i = 0; i < depth; i++)
        std::cout << '\t' << '|';
    std::cout << root->value << std::endl;
    print_tree(root->left, depth + 1);
    print_tree(root->right, depth + 1);
}

void search_precision(Binary_node* root, int left, int right){
    if(root->value < left){
        if(root->right)
            search_precision(root->right,left,right);
    }
    else if(root->value > right){
        if(root->left)
            search_precision(root->left,left,right);
    }
    else{
        std::cout << "(" << root->value << ")\n";
        if(root->right)
            search_precision(root->right,left,right);
        if(root->left)
            search_precision(root->left,left,right);
    }
}

std::vector <double> search_precision_vec(Binary_node* root , double left, double right){
    std::vector <double> res;
    std::vector <double> nw;
    if(root->value < left){
        if(root->right){
            nw = search_precision_vec(root->right,left,right);
            res.insert(res.end(),nw.begin(),nw.end());
        }
    }
    else if(root->value > right){
        if(root->left){
            nw = search_precision_vec(root->left,left,right);
            res.insert(res.end(),nw.begin(),nw.end());
        }
    }
    else{
        res.push_back(root->value);
        if(root->right){
            nw = search_precision_vec(root->right,left,right);
            res.insert(res.end(),nw.begin(),nw.end());
        }
        if(root->left){
            nw = search_precision_vec(root->left,left,right);
            res.insert(res.end(),nw.begin(),nw.end());
        }
    }
    return res;
}

