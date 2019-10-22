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

bool change_dir(tree_node<file>* &cur, const std::string &ch_dir, int mod){
    auto new_dir = cur;
    int len = ch_dir.length(), id = 0;
    std::string cur_dir;
    while(id < len){
        cur_dir = "";
        while(id < len && ch_dir[id] != '/'){
            cur_dir += ch_dir[id++];
        }
        if(cur_dir == ".."){
            if(new_dir->get_parent() != nullptr)
                new_dir = new_dir->get_parent();
            id++;
            continue;
        }
        bool found = false;
        for(int i = 0; i < new_dir->children.size(); i++)
            if(fits_value(new_dir->children[i], cur_dir)){
                if(new_dir->children[i]->get_level() <= mod){
                    new_dir = new_dir->children[i];
                    found = true;
                }else{
                    std::cout << "You don't have rights to interact with directory: \"" + cur_dir + "\".\n";
                    cur = new_dir;
                    return true;
                }
            }
        if(!found){
            return false;
        }
        id++;
    }
    cur = new_dir;
    return true;
}

int get_level(const std::string &pass){
    int l = 1, len = pass.length();
    if(pass[0] != '1')
        return l;
    for(int i = 1, n = std::min(5,len); i < n; i++){
        if((pass[i] - '0') == i+1)
            l++;
        else{
            std::cout << "no : " << (pass[i] - '0') << " != " << i+1 << std::endl;
            return l;
        }
    }

}
