//
// Created by sadoffnick on 11.10.19.
//

#ifndef LAB_1_FILE_H
#define LAB_1_FILE_H

#include <string>

class folder;

using namespace std;

class file {
private:
    string name;
    string creation_time;
    string change_time;
    int parent;
    char type;

public:

    string get_name();

    file(string _name, char _type, int cur_dir);

   // string set_time();
};

#endif //LAB_1_FILE_H


