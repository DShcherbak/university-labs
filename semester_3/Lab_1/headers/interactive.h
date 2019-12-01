//
// Created by sadoffnick on 20.10.19.
//

#ifndef LAB_1_INTERACTIVE_H
#define LAB_1_INTERACTIVE_H

#include "tree_node.h"
#include "my_file.h"

class User{
public:
    std::string username = "user";
    std::string comp = "@laptop";
    std::string current_path = "~";
    int DIR_COUNTER = 0;
    int mod = 1;
    tree_node<my_file>* root = new tree_node<my_file>(new my_file("root", "folder"), DIR_COUNTER++, mod);
    tree_node<my_file>* cur = root;
    vector <tree_node<my_file>*> catalog;


    void list(bool o = false, bool l = false);


    bool change_dir(const std::string &ch_dir);
    bool find_path(std::string &src_dir);
    int get_command_and_go();
    std::string get_path();

};




void print_greetings();

void print_manual();



int get_level(const std::string &pass);

#endif //LAB_1_INTERACTIVE_H
