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

    file root_file = *(new file("root","folder",DIR_COUNTER));
    tree_node<file>* root = new tree_node<file>(root_file);
    tree_node<file>* cur = root;
    vector <tree_node<file>*> catalog;
    catalog.push_back(root);

    bool wait_for_commands = true;
    while(wait_for_commands){
        std::cout << "\n" << username << comp << current_dir << "# ";
        std::cin >> command;
        if(command == "man")
        {
            print_manual();
        }
        else if (command == "cd"){
            std::string dir;
            std::cin >> dir;
          //  change_dir(cur,dir);
            std::cout << "Changing directory to " << current_dir << "/" << dir;
        }
        else if(command == "mkdir"){
            std::string dir;
            std::cin >> dir;

            //creating new directory in current directory
        }
        else if(command == "touch"){
            std::string filename;
            std::cin >> filename;
            //create new file
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