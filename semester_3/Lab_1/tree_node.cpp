//
// Created by sadoffnick on 11.10.19.
//

#include "tree_node.h"
#include <iostream>
#include <vector>
template <class T>
void tree_node<T>::set_parent(tree_node<T>* new_parent) {
    parent = new_parent;
}

template <class T>
void tree_node<T>::add_son(tree_node<T>* new_son){
    new_son->set_parent(this);
    children.push_back(new_son);
}

template <class T>
void tree_node<T>::delete_son(T val){
    for(int i = 0; i < children[i].size(); i++){
        if(val == children[i]){
            children.erase(children.begin()+i);
            return;
        }
    }
}

template <class T>
void tree_node<T>::delete_son(int id){
    if(children.size() <= id){
        std::cout << "ERROR. No such sun to delete.";
        return;
    }
    children.erase(children.begin()+id);
}

template <class T>
tree_node<T>* tree_node<T>::search_for_value(T val) {
    if(value == val){
        return this;
    }
    else{
        tree_node<T> *cur = nullptr;
        for(int i = 0; i < children.size(); i++){
            cur = children[i]->search_for_value(val);
            if(cur != nullptr)
                return cur;
        }
        return nullptr;
    }

}
