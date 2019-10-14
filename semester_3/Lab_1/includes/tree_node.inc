#include <iostream>
#include <vector>
#include <queue>



template <class T>
tree_node<T>::tree_node(T val) {
    value = val;
    parent = nullptr;
}

template <class T>
T tree_node<T>::get_value() {
    return value;
}


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

template <class T>
void tree_node<T>::delete_son(T val, bool _r){
    for(int i = 0; i < children.size(); i++){
        if(val == children[i]->get_value()){
            if(_r)
                delete_recursively(children[i]);
            else{
                save_sons(this, children[i]);
                delete children[i];
            }
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
        save_sons(children[id]);
        delete children[id];
    }
    children.erase(children.begin()+id);
    return;
}

template <class T>
tree_node<T>* tree_node<T>::search_for_value_dfs(T val) {
    std::cout << "dfs: " << value << std::endl;
    if(value == val){
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
tree_node<T>* tree_node<T>::search_for_value_bfs(T val) {
    std::queue <tree_node<T>*> Q;
    Q.push(this);
    tree_node<T>* cur;
    while(!Q.empty()){
        cur = Q.front();
        std::cout << "bfs: " << cur->value << std::endl;
        Q.pop();
        if(cur->get_value() == val)
            return cur;
        for(int i = 0; i < cur->children.size(); i++)
            Q.push(cur->children[i]);
    }
    return nullptr;
}