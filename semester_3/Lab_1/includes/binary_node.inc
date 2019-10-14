#include <iostream>
#include <vector>
#include <queue>



template <class T>
binary_node<T>::binary_node(T val) {
    value = val;
    parent = nullptr;
}

template <class T>
T binary_node<T>::get_value() {
    return value;
}


template <class T>
void binary_node<T>::set_parent(binary_node<T>* new_parent) {
    parent = new_parent;
}

template <class T>
void binary_node<T>::add_son(binary_node<T>* new_son){
    new_son->set_parent(this);
    if(left == nullptr && right == nullptr){
        int prob = rand()%2;
        if(prob)
            left = new_son;
        else
            right = new_son;
    }
    else if(left == nullptr)
        left = new_son;
    else if(right == nullptr)
        right = new_son;
    else{
        std::cout << "Error! Couldn't add son to " << get_value();
    }

}/*

template <class T>
void binary_node<T>::delete_son(T val){
    if(left->get_value() == val)

    for(int i = 0; i < children[i].size(); i++){
        if(val == children[i]){
            children.erase(children.begin()+i);
            return;
        }
    }
}

template <class T>
void binary_node<T>::delete_son_by_id(int id){
    if(children.size() <= id){
        std::cout << "ERROR. No such sun to delete.";
        return;
    }
    children.erase(children.begin()+id);
}

template <class T>
binary_node<T>* binary_node<T>::search_for_value_dfs(T val) {
    std::cout << "dfs: " << value << std::endl;
    if(value == val){
        return this;
    }
    else{
        binary_node<T> *cur = nullptr;
        for(int i = 0; i < children.size(); i++){
            cur = children[i]->search_for_value_dfs(val);
            if(cur != nullptr)
                return cur;
        }
        return nullptr;
    }

}

template <class T>
binary_node<T>* binary_node<T>::search_for_value_bfs(T val) {
    std::queue <binary_node<T>*> Q;
    Q.push(this);
    binary_node<T>* cur;
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
*/