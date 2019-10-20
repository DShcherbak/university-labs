/*#include "../headers/folder.h"
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

const int FOLDER_SIZE = 1;

void folder::add_subfolder(folder* f){
    subfolders.push_back(f);
}
void folder::add_file(file* f){
    files.push_back(f);
}

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

void folder::add_size(int s){
    size += s;
    if(parent)
        parent->add_size(s);
}

void add_folder_to_root(folder* &root, folder* &new_folder) {
    if(root == nullptr){
        root = new_folder;
        return;
    }
    root->add_subfolder(new_folder);
    root->add_size(FOLDER_SIZE);

}

void add_file_to_root(folder* &root, file* &new_file) {
    if(root == nullptr){
        cout << "ERROR! No such directory!\n";
        return;
    }
    root->add_file(new_file);
    root->add_size(FOLDER_SIZE);
}

Node* build_tree(){
    return nullptr;
}

void delete_tree(Node* &root){
    if(!root)
        return;
    for(auto ch: root->children)
        delete_tree(ch);
    delete root;
}

void folder::delete_folder(){
    for(auto sb: subfolders)
        sb->delete_folder();
    for(auto f: files)
        delete f;
    delete this;
}


void add_value_to_tree(Node* &root, int v){
    std::cout << "a" << (root ? "b" : "c") << "\n";
    Node* new_node = new Node(v);
//    add_node_to_root(root,new_node,probability);
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
        std::cout << "Empty tree.\n";
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
        if(root->children.size() > 0){
            int new_parent = randomInt(0, root->children.size()-1);
            for(int i = 0; i < root->children.size(); i++){
                if(i == new_parent)
                    continue;
                root->children[i]->parent = root->children[new_parent];
                root->children[new_parent]->children.push_back(root->children[i]);
            }
            if(root->parent)
                for(int i = 0, k = root->parent->children.size(); i < k; i++){
                    if(root->parent->children[i] == root) {
                        root->parent->children[i] = root->children[new_parent];
                        root->children[new_parent]->parent = root->parent;
                    }
                }
            //     std::cout << "New kids for " << root->parent->value << "\n";
            for(auto ch : root->parent->children)
                std::cout << ch->value << " ";
            //       std::cout << "\n";
        }
        delete root;
    }

}

*/