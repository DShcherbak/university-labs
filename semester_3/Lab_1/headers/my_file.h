//
// Created by sadoffnick on 11.10.19.
//

#ifndef LAB_1_MY_FILE_H
#define LAB_1_MY_FILE_H

#include <string>
#include <map>

class folder;

using namespace std;

class my_file {
private:
    string name;
    string creation_time;
    string change_time;
   // int parent;
    string type;
    int size;

public:

    string get_name();
    string get_creation_time();
    string get_change_time();
   // std::string get_path();
    string get_type();
    int get_size();

    my_file(std::string _name, std::string _type);

};
std::string to_string(my_file* a);

int get_inter(std::string s, int &id);

std::string parse_string(const std::string &request, std::map <int, pair<int,std::string>> &dict);

std::string paste_predicate(my_file* f, const std::string &predicate, std::map <int, pair<int,std::string>> &dict);

bool calculate_bool(const std::string &bool_eqw);

bool operator==(my_file* a, std::string b);


#endif //LAB_1_MY_FILE_H


