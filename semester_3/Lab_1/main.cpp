//
// Created by sadoffnick on 11.10.19.
//

#include "headers/file.h"
#include "headers/tree_node.h"
#include "headers/interactive.h"

#include <iostream>
#include <map>
#include <stdlib.h>


int main(){
    print_greetings();
    int DIR_COUNTER = 0;
    std::string username = "sadoffnick";
    std::string comp = "@laptop:";
    std::string current_dir = "~";
    std::string command;
    int mod = 1;

    file* root_file = new file("root","folder");
    tree_node<file>* root = new tree_node<file>(root_file, DIR_COUNTER++, mod);
    root->set_path("~");
    tree_node<file>* cur = root;
    vector <tree_node<file>*> catalog;
    catalog.push_back(root);

    bool wait_for_commands = true;
    while(wait_for_commands){
        std::cout << "\n" << username << comp << cur->get_path() << "# ";
        std::cin >> command;
        if(command == "man")
        {
            print_manual();
        }
        else if (command == "cd"){
            std::string dir;
            std::cin >> dir;
            if(!change_dir(cur,dir,mod))
                std::cout << "No such file or directory: "  << dir << "\n";
        }
        else if(command == "ls"){
            for(int i = 0; i < cur->children.size(); i++){
                std::cout << "~~" << to_string(cur->children[i]->get_value()) << std::endl;
            }
        }
        else if(command == "mkdir"){
            std::string dir;
            std::cin >> dir;
            auto new_dir = new file(dir,"folder");
            auto new_node = new tree_node<file>(new_dir, DIR_COUNTER++,mod);
            catalog.push_back(new_node);
            cur->add_son(new_node);//creating new directory in current directory
        }
        else if(command == "touch"){
            std::string filename;
            std::cin >> filename;
            auto new_file = new file(filename,"file");
            auto new_node = new tree_node<file>(new_file, DIR_COUNTER++,mod);
            catalog.push_back(new_node);
            cur->add_son(new_node);
        }
        else if(command == "chmod"){
            std::cout << "Enter your login: ";
            std::cin >> username;
            std::cout << "Enter your pass: ";
            std::string pass;
            std::cin >> pass;
            int level = get_level(pass);
            if(level > mod){
                std::cout << "You have increased your user rights\n";
                mod = level;
            }
            else if (level == mod){
                std::cout << "You have changed user.\n";
            }
            else{
                std::cout << "Your user rights were decreased.\n";
                mod = level;
                if(mod < cur->get_level()) {
                    std::cout << "You don't have rights to interact with this folder.\n";
                    std::cout << "You will be thrown to a folder with lower permission level.\n";
                    while (mod < cur->get_level()) {
                        cur = cur->get_parent();
                    }
                }
            }
        }
        else if(command == "exit"){
            wait_for_commands = false;
            std::cout << "Good bye!\n";
        }
        else{
            std::cout << "Unknown command: \"" + command + "\". \n";
            std::cout << "Please, try again, or read the manual to see the list of possible commands (simply write \"man\" into terminal.\n";
        }
    }
    delete_recursively(root);
    return 0;
}

/*std::cout << "Let's test that!\n";
    tree_node<int> *root;
    root = new tree_node<int>(3);
    std::cout << root->get_value() << std::endl;
    //delete root;

    std::vector<tree_node<int>*> node(5);
    for(int i = 0; i < 5; i++){
        node[i] = new tree_node<int>(i*i);
    }
    root->add_son(node[0]);
    root->add_son(node[3]);
    node[0]->add_son(node[1]);
    node[0]->add_son(node[2]);

    auto res = root->search_for_value_dfs(1);
    cout << (res == nullptr ? -1 : 1) << endl;
    auto res1 = root->search_for_value_bfs(1);
    cout << (res1 == nullptr ? -1 : 3) << endl;

    root->delete_son(0,false);

    res = root->search_for_value_dfs(4);
    std::cout << (res == nullptr ? -1 : 4) << std::endl;
*/