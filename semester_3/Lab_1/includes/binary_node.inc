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

}
template <class T>
void binary_node<T>::delete_son(T val, bool _r){
    if(fits_value(left,val)) {
        if (_r)
            delete_recursively(left);
        else
            save_sons_and_delete(this, left);
        left = nullptr;
    }
    if(fits_value(right,val)){
        if(_r)
            delete_recursively(right);
        else
            save_sons_and_delete(this, right);
        right = nullptr;
    }
}

template <class T>
binary_node<T>* binary_node<T>::search_for_value_dfs(T val) {
    // std::cout << "dfs: " << value << std::endl;
    if(fits_value(this,val)){
        return this;
    }
    else{
        binary_node<T> *cur = nullptr;
        cur = left->search_for_value_dfs();
        if(cur != nullptr)
            return cur;
        cur = right->search_for_value_dfs();
        if(cur != nullptr)
            return cur;
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
        //     std::cout << "bfs: " << to_string(cur->get_value()) << std::endl;
        Q.pop();
        if(fits_value(cur,val))
            return cur;
        Q.push(cur->left);
        Q.push(cur->right);

    }
    return nullptr;
}

