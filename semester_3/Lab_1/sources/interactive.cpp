//
// Created by sadoffnick on 20.10.19.
//

#include "../headers/interactive.h"
#include "../headers/file.h"
#include "../headers/tree_node.h"
#include <iostream>
#include <map>
#include <set>

map <std::string, int> command_dict = {{"exit", 0},{"man", 1}, {"ls", 2}, {"cd",3}, {"mkdir", 4}, {"touch", 5}, {"src", 6}, {"mv", 7}, {"cp" ,8}};
set <std::string> exists = {"exit", "man", "ls", "cd", "mkdir", "touch", "src", "mv", "cp"};

std::string get_word(std::string source, int id){
    int len = source.length(); std::string result = "";
    while(id < len && source[id] == ' ')
        id++;
    while(id < len && source[id] != ' ')
        result += source[id++];
    while(id < len && source[id] == ' ')
        id++;

}

int get_command_and_go(User* user){
    std::string line, command, temp;
    getline(std::cin, line);
    std::vector <std::string> argv;
    int argc = 0, id = 0;
    command = get_word(line, id);
    if(exists.count(command) == 0){
        std::cout << "Error! No such command: \"" << command << "\"\n";
        return 1;
    }


    int command_code = command_dict[command];
    switch(command_code){
        case 0:
            return false;
        case 1:
            print_manual();
            return true;
        case 2:

    }

}

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


bool find_path(tree_node<file>* &cur, std::string &ch_dir, int mod){
    std::cout << "Would you like to use bfs or dfs for the search? Type 'b' if dfs and 'd' otherwise: ";
    char c;
    std::cin >> c;

    auto new_dir= cur;
    auto src_dir = cur;
    int len = ch_dir.length(), id = 0;
    std::string cur_dir;
    while(id < len){
        cur_dir = "";
        while(id < len && ch_dir[id] != '/'){
            cur_dir += ch_dir[id++];
        }
        src_dir = new_dir->search_for_value_bfs(cur_dir);
        if(src_dir == nullptr) {
            ch_dir = cur_dir;
            return false;
        }
        else if(src_dir->get_level() <= mod){
            new_dir = src_dir;
        }else{
            std::cout << "You don't have rights to interact with directory: \"" + cur_dir + "\".\n";
            cur = new_dir;
            return true;
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
