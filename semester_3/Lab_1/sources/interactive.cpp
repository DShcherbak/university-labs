//
// Created by sadoffnick on 20.10.19.
//

#include "../headers/interactive.h"
#include "../headers/my_file.h"
#include "../headers/tree_node.h"
#include <iostream>
#include <map>
#include <set>

map <std::string, int> command_dict = { {"exit", 0},{"man", 1}, {"ls", 2}, {"cd",3}, {"mkdir", 4}, {"touch", 5}, {"src", 6}, {"chmod", 7}};//, {"mv", 8}, {"cp" ,9} };
map <std::string, set <std::string>> possible_specifiers = { {"exit", {}},{"man", {}}, {"ls", {"l", "o"}}, {"cd",{}}, {"mkdir", {}}, {"touch", {}}, {"src", {"b","f","r"}}, {"chmod", {}}};
set <std::string> exists = {"exit", "man", "ls", "cd", "mkdir", "touch", "src", "mv", "cp"};

void User::list(bool o, bool l){
    if(l){
        //TODO: implement listing with all information
    }else{
        char ser = (o ? '\n' : ' ');
        for(int i = 0, n = cur->children.size(); i < n; i++){
            std::cout << cur->children[i]->get_value()->get_name() << ser;
        }

    }
}

std::string get_word(std::string source, int &id){
    int len = source.length(); std::string result = "";
    while(id < len && (source[id] == ' ' || source[id] == '-'))
        id++;
    while(id < len && source[id] != ' ')
        result += source[id++];
    while(id < len && source[id] == ' ')
        id++;
    return result;
}

int User::get_command_and_go(){
    std::cout << "\n" << username << comp << get_path() << "# ";
    std::string line, command, temp;
    getline(std::cin, line);
    std::vector <std::string> specifier_values, argv;
    int argc = 0, specifier_counter = 0, id = 0;
    command = get_word(line, id);
    if(exists.count(command) == 0){
        std::cout << "Error! No such command: \"" << command << "\"\n";
        return 1;
    }
    while(id < line.length() && line[id] == '-'){
            specifier_values.push_back(get_word(line,id));
            specifier_counter++;

    }
    while(id < line.length()){
            argv.push_back(get_word(line,id));
            argc++;
    }


    std::string dir;
    std::string file;
    std::string path;
    my_file* new_dir;
    std::string pass;
    int level;
    tree_node<my_file>* new_node;
    auto new_file = new my_file(file, "my_file");
    int command_code = command_dict[command];
    switch(command_code){
        case 0:
            return 0;
        case 1:
            print_manual();
            return 1;
        case 2:
            list();
            return 1;
        case 3:
            change_dir(argv[0]); // TODO: not change directory if file not folder
            return 1;
        case 4:
            new_dir = new my_file(argv[0], "folder");
            new_node = new tree_node<my_file>(new_dir,DIR_COUNTER++,mod); //TODO: stop creating same-named files
            catalog.push_back(new_node);
            cur->add_son(new_node);//creating new directory in current directory
            return 1;
        case 5:
            new_dir = new my_file(argv[0], "my_file");
            new_node = new tree_node<my_file>(new_dir, DIR_COUNTER++,mod);
            catalog.push_back(new_node);
            cur->add_son(new_node);//creating new file in current directory
            return 1;
        case 6:
            if (!find_path(path))
                std::cout << "No such my_file or directory: " << path << "\n";
        case 7:
            std::cout << "Enter your login: ";
            std::cin >> username;
            std::cout << "Enter your pass: ";
            std::cin >> pass;
            level = get_level(pass);
            if(level > mod){
                std::cout << "You have increased your user rights\n";
            }
            else if (level == mod){
                std::cout << "You have changed user.\n";
            }
            else{
                std::cout << "Your user rights were decreased.\n";
                if(level < cur->get_level()) {
                    std::cout << "You don't have rights to interact with this folder.\n";
                    std::cout << "You will be thrown to a folder with lower permission level.\n";
                    while (level < cur->get_level()) {
                        cur = cur->get_parent();
                    }
                }
            }
            mod = level;
            return 1;
        default:
            return 0;
    }
//{"src", 6}, {"mv", 7}, {"cp" ,8} };
}

std::string User::get_path(){
    return current_path;
}

void print_greetings(){
    std::cout << "Hello, dear user!\n";
    std::cout << "...\n";
}

void print_manual(){
    std::cout << "Here's the list of possible commands:\n";
}

bool User::change_dir(const std::string &ch_dir){
    auto new_dir = cur;
    std::string changed_path = current_path;
    int len = ch_dir.length(), id = 0;
    std::string cur_dir;
    while(id < len){
        cur_dir = "";
        while(id < len && ch_dir[id] != '/'){
            cur_dir += ch_dir[id++];
        }
        if(cur_dir == ".."){
            if(new_dir->get_parent() != nullptr){
                std::cout << "Changed path: " << changed_path << std::endl;
                new_dir = new_dir->get_parent();
                while(changed_path[changed_path.length()-1] == '/')
                    changed_path.pop_back();
                std::cout << "Changed path: " << changed_path << std::endl;

            }
            id++;
            continue;
        }


        bool found = false;
        for(int i = 0; i < new_dir->children.size(); i++)
            if(fits_value(new_dir->children[i], cur_dir)){
                if(new_dir->children[i]->get_level() <= mod){
                    std::cout << "Changed path: " << changed_path << std::endl;
                    changed_path += cur_dir;
                    std::cout << "Changed path: " << changed_path << std::endl;

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
    current_path = cur->get_path();
    return true;
}


bool User::find_path(std::string &ch_dir){
    std::cout << "Would you like to use bfs or dfs for the search? Type 'b' if bfs and 'd' otherwise: ";
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
