//
// Created by sadoffnick on 11.10.19.
//

#include "headers/my_file.h"
#include "headers/tree_node.h"
#include "headers/interactive.h"

#include <iostream>
#include <map>
#include <stdlib.h>


int main(){
    print_greetings();
    int DIR_COUNTER = 0;
    std::string command;
    int mod = 1;

    auto root_file = new my_file("root", "folder");
    auto root = new tree_node<my_file>(root_file, DIR_COUNTER++, mod);
    root->set_path("~");
    tree_node<my_file>* cur = root;


    User *user = new User();
    user->catalog.push_back(root);

    bool wait_for_commands = true;
    while(wait_for_commands) {
        if (user->get_command_and_go() == 0){
            wait_for_commands = false;
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