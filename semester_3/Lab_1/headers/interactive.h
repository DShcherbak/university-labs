//
// Created by sadoffnick on 20.10.19.
//

#ifndef LAB_1_INTERACTIVE_H
#define LAB_1_INTERACTIVE_H

#include "tree_node.h"
#include "file.h"

class User{
public:
    std::string username = "user";
    std::string comp = "@laptop";
    std::string current_dir = "~";
    int DIR_COUNTER = 0;
    int mod = 1;
    tree_node<file>* root = new tree_node<file>(new file("root","folder"), DIR_COUNTER++, mod);
    tree_node<file>* cur = root;

    void list(bool o = false, bool l = false);

};

int get_command_and_go(User* user);


void print_greetings();

void print_manual();

bool change_dir(tree_node<file>* &cur, const std::string &ch_dir, int mod);

bool find_path(tree_node<file>* &cur, std::string &ch_dir, int mod);

int get_level(const std::string &pass);

#endif //LAB_1_INTERACTIVE_H
