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
void tree_node<T>::delete_son(T val){
    for(int i = 0; i < children[i].size(); i++){
        if(val == children[i]){
            children.erase(children.begin()+i);
            return;
        }
    }
}

template <class T>
void tree_node<T>::delete_son_by_id(int id){
    if(children.size() <= id){
        std::cout << "ERROR. No such sun to delete.";
        return;
    }
    children.erase(children.begin()+id);
}

template <class T>
tree_node<T>* tree_node<T>::search_for_value_dfs(T val) {
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

template <class T>
tree_node<T>* tree_node<T>::search_for_value_bfs(T val) {
    std::queue <int> Q;
    Q.push(this);
    tree_node<T>* cur;
    while(!Q.empty()){
        cur = Q.front();
        Q.pop();
        if(cur->value == val)
            return cur;
        for(int i = 0; i < children.size(); i++)
            Q.push(children[i]);

    }
}
