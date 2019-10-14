//
// Created by sadoffnick on 11.10.19.
//

#include "headers/folder.h"
#include "headers/tree_node.h"
#include <iostream>



int main(){
    std::cout << "Let's test that";
    tree_node<int> *root;
    root = new tree_node<int>(3);
    std::cout << root->get_value() << std::endl;
    //delete root;

    std::vector<tree_node<int>*> node(5);
    for(int i = 0; i < 5; i++){
        node[i] = new tree_node<int>(i*i);
    }
    root->add_son(node[0]);
    root->add_son(node[3]);
    node[0]->add_son(node[1]);
    node[0]->add_son(node[2]);

    auto res = root->search_for_value_dfs(1);
    cout << (res == nullptr ? -1 : 1) << endl;
    auto res1 = root->search_for_value_bfs(1);
    cout << (res1 == nullptr ? -1 : 3) << endl;

    root->delete_son(0,true);

    res = root->search_for_value_dfs(1);
    cout << (res == nullptr ? -1 : 1) << endl;


    return 0;
}