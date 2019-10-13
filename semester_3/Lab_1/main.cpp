//
// Created by sadoffnick on 11.10.19.
//

#include "folder.h"
#include "tree_node.h"
#include <iostream>



int main(){
    std::cout << "Let's test that";
    tree_node<int> *root;
    root = new tree_node<int>(3);
    std::cout << root->get_value() << std::endl;
    delete root;
    return 0;
}