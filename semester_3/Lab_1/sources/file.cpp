#include "../headers/file.h"
#include <cctype>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


std::string convert_month(int n){
    return n < 9 ? '0' + std::to_string(n + 1) : std::to_string(n + 1);
}

std::string convert_time(tm* t){
    return std::to_string((*t).tm_hour+3) +':'+ std::to_string((*t).tm_min) +':'+ std::to_string((*t).tm_sec) + " " + std::to_string((*t).tm_mday) +'.'+ convert_month((*t).tm_mon) +'.'+ std::to_string((*t).tm_year+1900);
}

string get_time(){
    time_t now = time(nullptr);
    tm *gmtm = gmtime(&now);
    return convert_time(gmtm);
}

file::file(string _name, char _type, int cur_dir){
    name = _name;
    creation_time = get_time();
    change_time = creation_time;
    type = _type;
    parent = cur_dir;
}

string file::get_name(){
    return name;
}

bool operator==(file a, file b){
    return (a.get_name() == b.get_name());
}


