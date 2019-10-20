//
// Created by sadoffnick on 11.10.19.
//

#ifndef LAB_1_FILE_H
#define LAB_1_FILE_H

#include <string>
#include <map>

class folder;

using namespace std;

class file {
private:
    string name;
    string creation_time;
    string change_time;
    int parent;
    string type;

public:

    string get_name();
    string get_creation_time();
    string get_change_time();
    int get_parent();
    string get_type();

    file(std::string _name, std::string _type, int cur_dir);

   // string set_time();
};
int get_inter(std::string s, int &id);

std::string parse_string(std::string request, std::map <int, pair<int,std::string>> &dict);

std::string paste_predicat(file* f, std::string predicat,std::map <int, pair<int,std::string>> dict);

bool calculate_bool(std::string &bool_eqw);

#endif //LAB_1_FILE_H


