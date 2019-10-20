//
// Created by sadoffnick on 20.10.19.
//

#include "../headers/interactive.h"
#include "../headers/file.h"
#include "../headers/tree_node.h"
#include <iostream>



void print_greetings(){
    std::cout << "Hello, dear user!\n";
    std::cout << "...\n";
}

void print_manual(){
    std::cout << "Here's the list of possible commands:\n";
}

void change_dir(tree_node<file>* &cur, const std::string &ch_dir){
    auto new_dir = cur;
    int len = ch_dir.length(), id = 0;
    std::string cur_dir;
    while(id < len){
        cur_dir = "";
        while(id < len && ch_dir[id] != '/'){
            cur_dir += ch_dir[id++];
        }
        if(cur_dir == ".."){
            new_dir = new_dir->get_parent();
            continue;
        }
        bool found = false;
        for(int i = 0; i < new_dir->children.size(); i++)
            if(fits_value(new_dir->children[i], cur_dir)){
                new_dir = new_dir->children[i];
                found = true;
            }
        if(!found){
            std::cout << "No such directory: " << ch_dir << std::endl;
            return;
        }
        id++;
    }
    cur = new_dir;

}

