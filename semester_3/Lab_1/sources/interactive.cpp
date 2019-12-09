//
// Created by sadoffnick on 20.10.19.
//

#include "../headers/interactive.h"
#include "../headers/my_file.h"
#include "../headers/tree_node.h"
#include <iostream>
#include <map>
#include <set>
#include <iomanip>




command::command(std::string _name, int _code, set<std::string> _possible, int _amount_of_specifiers, int _amount_of_arguments)
                : name (_name),
                  code (_code),
                  possible_specifiers (std::move(_possible)),
                  amount_of_specifiers (_amount_of_specifiers),
                  amount_of_arguments (_amount_of_arguments){
}

map <int, set <std::string>> possible_specifiers = { {0, {}},{1, {}}, {2, {"l", "o"}}, {3,{}}, {4, {}}, {5, {}}, {6, {"b","f","r"}}, {7, {}}};
set <std::string> exists = {"exit", "man", "ls", "cd", "mkdir", "touch", "src", "chmod", "rm"};

User::User() {
    root->set_path("~");
    commands[0] = new command("exit", 0, {}, 0, 0);
    commands[1] = new command("man", 1, {}, 0, 0);
    commands[2] = new command("ls", 2, {"l", "o"}, 2, 0);
    commands[3] = new command("cd", 3, {}, 0, 1);
    commands[4] = new command("mkdir", 4, {}, 0, 1);
    commands[5] = new command("touch", 5, {}, 0, 1);
    commands[6] = new command("src", 6, {"b", "d", "r"}, 3, 1);
    commands[7] = new command("chmod", 7, {}, 0, 0);
    commands[8] = new command("rm", 8, {"r"}, 1, 0);

}

map <std::string, int> command_dict = { {"exit", 0},{"man", 1}, {"ls", 2}, {"cd",3}, {"mkdir", 4}, {"touch", 5}, {"src", 6}, {"chmod", 7}, {"rm", 8}};//, {"mv", 9}, {"cp" ,10} };


User::~User(){
    delete_recursively(root);
}

void User::list(std::vector <bool> specifiers){

        char separator;
        std::string additional_info;
        if(specifiers[0]){
            std::cout << std:: setw(10) << "type " << " | " << std::setw(18) << "creation time " << " | " << std:: setw(18) << "change time " <<  " | " << std:: setw(10) << "name" << std::endl;
            std::cout << "------------------------------------------------------------------------------------------\n";
        }
    for(auto & child : cur->children){
            if(specifiers[0]){
                std::cout << std:: setw(10) << child->get_value()->get_type() << " | ";
                std::cout << std:: setw(18) << child->get_value()->get_creation_time() << " | ";
                std::cout << std:: setw(18) << child->get_value()->get_change_time() << " | ";
            }
            separator = (specifiers[0] || specifiers[1] ? '\n' : ' ');
            std::cout  << child->get_value()->get_name() << separator;
        }
    std::cout << std::endl;
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

int get_id(int command, std::string specifier){
    if(command == 2){
        if(specifier == "l")
            return 0;
        if(specifier == "o")
            return 1;
        return -1;
    }
    if(command == 6){
        if(specifier == "b")
            return 0;
        if(specifier == "d")
            return 1;
        if(specifier == "r")
            return 2;
        return -1;
    }
    return -1;
}

std::vector <bool> specifiers_into_vector(int command_code, std::vector <std::string> spec){
    if(command_code == 2 || command_code == 6) {
        std::vector <bool> result(possible_specifiers[command_code].size());
        for(int i = 0; i < spec.size(); i++)
            result[get_id(command_code,spec[i])] = true;
        return result;
    }
    else
        return {};
}

int User::get_command_and_go(){
    std::cout << username << comp << get_path() << "# ";
    std::string line, command, temp;
    getline(std::cin, line);
    std::vector <std::string> specifier_values, argv;
    int argc = 0, specifier_counter = 0, id = 0;
    command = get_word(line, id);
    if(exists.count(command) == 0){
        std::cout << "Error! No such command: \"" << command << "\"\n";
        return 1;
    }
    auto current_command = commands[command_dict[command]];


    while(id < line.length() && line[id] == '-'){
            specifier_values.push_back(get_word(line,id));
            specifier_counter++;
    }
    for(auto & s : specifier_values){
        if(current_command->possible_specifiers.count(s) == 0){
            std::cout << "No such specifier: -" << s << std::endl;
            return 1;
        }
    }


    while(id < line.length()){
        argv.push_back(get_word(line,id));
        argc++;
    }
    if(argc > current_command->amount_of_arguments)
        std::cout << "Too many arguments!\n";
    else if (argc < current_command->amount_of_arguments)
        std::cout << "Not enough arguments!\n";
    if(argc != current_command->amount_of_arguments)
        return 1;


    my_file* new_dir;
    std::string pass;
    int level;
    tree_node<my_file>* new_node;
    int command_code = command_dict[command];
    switch(command_code){
        case 0:
            return 0;
        case 1:
            print_manual();
            return 1;
        case 2:
            list(specifiers_into_vector(command_code,specifier_values));
            return 1;
        case 3:
            change_dir(argv[0]);
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
            if (!find_path(argv[0]))
                std::cout << "No such my_file or directory: " << argv[0] << "\n";
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
                        current_path = cur->get_path();
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

tree_node<my_file>* node_by_path(){

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
                new_dir = new_dir->get_parent();
                while(changed_path[changed_path.length()-1] == '/')
                    changed_path.pop_back();
            }
            id++;
            continue;
        }


        bool found = false;
        for(int i = 0; i < new_dir->children.size(); i++)
            if(fits_value(new_dir->children[i], cur_dir)){
                if(new_dir->children[i]->get_value()->get_type() == "folder") {
                    if (new_dir->children[i]->get_level() <= mod) {
                        changed_path += "/" + cur_dir;
                        new_dir = new_dir->children[i];
                        new_dir->set_path(changed_path);
                        found = true;
                    } else {
                        std::cout << "You don't have rights to interact with directory: \"" + cur_dir + "\".\n";
                        cur = new_dir;
                        return true;
                    }
                }
                else{
                    std::cout << "No such directory: \"" + cur_dir + "\".\n";
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
        else
            return l;
    }
}

