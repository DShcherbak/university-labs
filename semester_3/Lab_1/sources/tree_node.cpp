//
// Created by sadoffnick on 11.10.19.
//

#include "../headers/tree_node.h"
#include "../headers/my_file.h"
#include <string>


bool fits_value(tree_node<int>* node, int v){
    return *(node->get_value()) == v;
}


bool fits_value(tree_node<double>* node, double v){
    return *(node->get_value()) == v;
}


bool fits_value(tree_node<std::string>* node, std::string v){
    return *(node->get_value()) == v;
}


bool fits_value(tree_node<my_file>* node, std::string request){
    return to_string(node->get_value()) == request;
}

