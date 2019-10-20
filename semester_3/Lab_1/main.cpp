//
// Created by sadoffnick on 11.10.19.
//

#include "headers/folder.h"
#include "headers/tree_node.h"

#include <iostream>
#include <map>


int main(){
    std::cout << "Let's test that!\n";
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



    std::map <int, pair<int,std::string>> dict;

    int id = 0;

    std::string s = "A";
    //std::string predicat = parse_string("name='a' | type='b' & name='c'",dict);
    std::string predicat = parse_string("((name='al+lo' | type='illla')  ! (type='illa' & name='name'))", dict);

    //
    std::cout << predicat << std::endl;

    file* f = new file("name", "illa", 0);

    std::string bool_eqw =paste_predicat(f,predicat, dict);

    std::cout << bool_eqw << std::endl;

   cout << (calculate_bool(bool_eqw) ? "Fits.\n" : "Doesn't fit.\n");


    return 0;
}