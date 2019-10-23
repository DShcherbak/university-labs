//
// Created by sadoffnick on 20.10.19.
//

#ifndef LAB_1_INTERACTIVE_H
#define LAB_1_INTERACTIVE_H

#include "tree_node.h"
#include "file.h"

void print_greetings();

void print_manual();

bool change_dir(tree_node<file>* &cur, const std::string &ch_dir, int mod);

bool find_path(tree_node<file>* &cur, std::string &ch_dir, int mod);

int get_level(const std::string &pass);

#endif //LAB_1_INTERACTIVE_H
