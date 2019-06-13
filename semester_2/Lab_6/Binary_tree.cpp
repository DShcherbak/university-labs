#pragma once
#include <iostream>
#include <random>
#include "Binary_tree.h"
#include "element.h"

struct Node{
    element* elem;
    Node* parent, *left, *right;

    Node(element* e){
        elem = e;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
};

int randomInt(int begin, int end){
    static std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

Binary_tree* Binary_tree::create_empty(){
    Binary_tree* lst = new Binary_tree();
    lst->root = nullptr;
    return lst;
}

void Binary_tree::add_node(Node* new_node){
    if(root == nullptr){
        root = new_node;
        return;
    }
    Node* cur = root;
    Node* prev = nullptr;
    bool left_son;
    while(cur){
        if(cur->elem->val < new_node->elem->val){
            prev = cur;
            cur = cur->right;
            left_son = false;
        }
        else{
            prev = cur;
            cur = cur->left;
            left_son = true;
        }
    }
    cur = new_node;
    cur->parent = prev;
    if(prev && left_son)
        prev->left = cur;
    else
        prev->right = cur;


}


void add_tree_to_root(Binary_tree* &tree, Node* &root, Node* son){
    if(!son)
        return;
    add_tree_to_root(tree,root,son->left);
    add_tree_to_root(tree,root,son->right);
    tree->add_element(root->elem->val);
}

void delete_node_by_value(Binary_tree* tree, Node* &root, int value){
    if(!root)
        return;
    delete_node_by_value(tree, root->left, value);
    delete_node_by_value(tree, root->right, value);
    Node* temp,*son;
    if(root->elem->val == value){
        int new_parent = randomInt(0,1);
        if(new_parent){
            temp = root->left;
            son = root->right;
            delete root;
            root = temp;
            add_tree_to_root(tree,root,son);
        }

    }
}

void Binary_tree::delete_element(int value) {
    delete_node_by_value(this, root, value);
}

void Binary_tree::add_element(int value){
    element* elem = new element(value);
    Node* new_node = new Node(elem);
    Binary_tree::add_node(new_node);

}

int find_node_by_range(Node* root, int st, int fin){
    if(!root)
        return 0;
    int cnt = 0;
    int val = root->elem->val;
    if(val >= st && val <= fin)
        cnt++;
    if(val < st)
        return find_node_by_range(root->right,st,fin);
    else if (val > fin)
        return find_node_by_range(root->left,st,fin);
    else
        return find_node_by_range(root->right,st,fin) + find_node_by_range(root->left,st,fin) + cnt;
}

int Binary_tree::find_by_range(int st,int fin) {
    return find_node_by_range(root,st,fin);
}

void print_binary_tree_right(Node* root){
    if(!root){
        std::cout << "Empty tree.\n";
        return;
    }
    std::cout << root->elem->val << " ";
    if(root->left)
        print_binary_tree_right(root->left);
    if(root->right)
        print_binary_tree_right(root->right);
}

void Binary_tree::print(){
    print_binary_tree_right(root);
    std::cout << ".\n";
}
