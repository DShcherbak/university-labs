//
// Created by sadoffnick on 11.10.19.
//

#include "../headers/tree_node.h"


template <class T>
void save_sons(tree_node<T>* parent, tree_node<T>* cur){
    for(int i = 0; i < cur->children.size(); i++){
        parent->add_son(cur->children[i]);
    }
}


template <class T>
void delete_recursively(tree_node<T>* cur){
    for(int i = 0; i < cur->children.size(); i++)
        delete_recursively(cur->children[i]);
    delete cur;
}