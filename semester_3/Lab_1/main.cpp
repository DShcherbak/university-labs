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
    User *user = new User();
    user->root->set_path("~");

    while(true)
        if (user->get_command_and_go() == 0)
            break;


    delete user;
    return 0;
}

