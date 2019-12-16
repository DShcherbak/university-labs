#include <iostream>
#include <vector>
#include <queue>
#include "../headers/my_file.h"
#include "../library/verbalexpressions.hpp"



template <class T>
tree_node<T>::tree_node(T* val, int _id, int _level) {
    value = val;
    parent = nullptr;
    id = _id;
    level = _level;
}

template <class T>
T* tree_node<T>::get_value() {
    return value;
}

template <class T>
tree_node<T>* tree_node<T>::get_parent() {
    return parent;
}
template <class T>
std::string tree_node<T>::get_path() {
    return path;
}

template <class T>
int tree_node<T>::get_id() {
    return id;
}

template <class T>
int tree_node<T>::get_level() {
    return level;
}



template <class T>
void tree_node<T>::set_parent(tree_node<T>* new_parent) {
    parent = new_parent;
    path = parent->get_path() + "/" +  to_string(get_value());
}

template <class T>
void tree_node<T>::set_path(std::string _path) {
    path = _path;
}

template <class T>
void tree_node<T>::add_son(tree_node<T>* new_son){
    new_son->set_parent(this);
    new_son->set_path(this->get_path() + "/" + new_son->get_value()->get_name());
    children.push_back(new_son);
}


template <class T>
void save_sons_and_delete(tree_node<T>* parent, tree_node<T>* cur){
    for(int i = 0; i < cur->children.size(); i++){
        parent->add_son(cur->children[i]);
        std::cout << parent->get_value() << " -> " << cur->children[i]->get_value() << std::endl;
    }
    delete cur;
}


template <class T>
void delete_recursively(tree_node<T>* cur){
    for(int i = 0; i < cur->children.size(); i++)
        delete_recursively(cur->children[i]);
    delete cur;
}

template <class T>
void tree_node<T>::delete_son(T val, bool _r){
    for(int i = 0; i < children.size(); i++){
        if(fits_value(children[i],val)){
            if(_r)
                delete_recursively(children[i]);
            else
                save_sons_and_delete(this, children[i]);
            children.erase(children.begin()+i);
            return;
        }
    }
}

template <class T>
void tree_node<T>::delete_son_by_id(int id, bool _r){
    if(children.size() <= id){
        std::cout << "ERROR. No such sun to delete.";
        return;
    }
    if(_r)
        delete_recursively(children[id]);
    else{
        save_sons_and_delete(this, children[id]);
    }
    children.erase(children.begin()+id);
    return;
}
template <class T>
bool fits_value(tree_node<T>* cur, T val){
    return true;
}

template <class T>
bool fits_value(tree_node<T>* cur, std::string name){
    verex::verex expr = verex::verex()
            .search_one_line()
            .start_of_line()
            .add(name)
            .end_of_line();
    std::string val= to_string(cur->get_value());
    return expr.test(val);// == name;
}

template <class T>
tree_node<T>* tree_node<T>::search_for_value_dfs(std::string val) {
   // std::cout << "dfs: " << value << std::endl;
    if(fits_value(this,val)){
        return this;
    }
    else{
        tree_node<T> *cur = nullptr;
        for(int i = 0; i < children.size(); i++){
            cur = children[i]->search_for_value_dfs(val);
            if(cur != nullptr)
                return cur;
        }
        return nullptr;
    }
}

template <class T>
tree_node<T>* tree_node<T>::search_for_value_bfs(std::string val) {
    std::queue <tree_node<T>*> Q;
    Q.push(this);
    tree_node<T>* cur;
    while(!Q.empty()){
        cur = Q.front();
   //     std::cout << "bfs: " << to_string(cur->get_value()) << std::endl;
        Q.pop();
        if(fits_value(cur,val))
            return cur;
        for(int i = 0; i < cur->children.size(); i++)
            Q.push(cur->children[i]);
    }
    return nullptr;
}


template <class T>
void find_and_delete(tree_node<T>* root, T* val, bool _r){
    tree_node<T>* target = root->search_for_value_bfs(val);
    if(_r)
        delete_recursively(target);
    else
        save_sons_and_delete(target->get_parent(), target);
}