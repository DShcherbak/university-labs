#include "../headers/file.h"
#include <cctype>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <stack>


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

file::file(std::string _name, std::string _type, int cur_dir){
    name = _name;
    creation_time = get_time();
    change_time = creation_time;
    type = _type;
//    parent = cur_dir;
}

string file::get_name(){
    return name;
}

string file::get_creation_time(){
    return creation_time;
}

string file::get_change_time(){
    return change_time;
}

/*
int file::get_parent(){
    return parent;
}

*/
string file::get_type(){
    return type;
}

bool operator==(file a, file b){
    return (a.get_name() == b.get_name());
}

int index(string param){
    if(param == "name")
        return 0;
    if(param == "created")
        return 1;
    if(param == "change")
        return 2;
    if(param == "parent")
        return 3;
    if(param == "type")
        return 4;
    std::cout << "Unknown type error!\n";
    return 8;// unknown type error
}

void throw_error(std::string e){
    cout << "ERROR!\n";
    cout << e << std::endl;
}

std::string get_param(std::string s, int &id){
    std::string param = "";
    while(isalpha(s[id]))
        param += s[id++];
    if(s[id] == '=' || s[id] == ' ')
        return param;
    else
        return (param + s[id]);
}

std::string word_with_brackets(std::string s, int &id, int len){
    std::string word = "";
    if(s[id] != '\'')
        return "";
    id++;
    while(id < len && s[id] != '\'')
        word += s[id++];
    if(id == len)
        return "";
    id++;
    return word;
}

bool is_operator(char c){
    return c == '!'
           || c == '&'
           || c == '|'
           || c == ','
           || c == '('
           || c == ')';
}

std::string parse_string(const std::string &request, std::map <int, pair<int,std::string>> &dict){
    int len = request.length();
    int id = 0, counter = 0;
    std::set <std::string> values;
    std::string result = "";
    while(id < len){
        if(request[id] == ' ')
            id++;
        else if(is_operator(request[id])){
            result += (request[id] == ',' ? '&' : request[id]);
            id++;
            continue;
        }
        else if(isalpha(request[id])){
            std::string param = get_param(request,id);
            if(request[id] != '=' || index(param) == 8){
                throw_error("Wrong parameter name: \"" + param + "\"");
                return "";
            }
            id++;//=
            std::string value = word_with_brackets(request,id,len);
            if(value == ""){
                throw_error("\' not found.");
                return "";
            }
            dict[counter] = {index(param),value};
            result += '[';
            result += to_string(counter);
            result += ']';
            counter++;
        }
        else{
            throw_error("Unknown symbol ");
            std::cout << (char) request[id] << "\n";
            return "";
        }
    }
    return result;
}

int get_inter(std::string s, int &id){
    int result = 0, len = s.length();
    while(id < len && '0' <= s[id] && s[id] <= '9'){
        result *= 10;
        result += (int) (s[id++] - '0');
    }
    return result;
}

bool bool_value(file* f, int hash, std::map <int, pair<int,std::string>> &dict){
    auto v = dict[hash];
    int id = 0;
    switch(v.first){
        case 0:
            return f->get_name() == v.second;
        case 1:
            return f->get_creation_time() == v.second;
        case 2:
            return f->get_change_time() == v.second;
//        case 3:
  //          return f->get_parent() == get_inter(v.second,id);
        case 4:
            return f->get_type() == v.second;
        default:
            return false;
    }
}

std::string paste_predicate(file* f, const std::string &predicate, std::map <int, pair<int,std::string>> &dict){
    std::string result = "";
    int len = predicate.length(), id = 0;
    while(id < len){
        if(predicate[id] == '['){
            id++;
            int hash = get_inter(predicate,id);
            result += std::to_string(bool_value(f, hash, dict));
            id++;
        }
        else
            result += predicate[id++];
    }
    return result;
}

void perform(char op, stack<bool> &operands){
    if(op == '!'){
        bool cur = operands.top();
        operands.pop();
        operands.push(!cur);
        return;
    }
    else if(op == '&'){
        bool r = operands.top();
        operands.pop();
        bool l = operands.top();
        operands.pop();
        operands.push(l&r);
    }
    else{
        bool r = operands.top();
        operands.pop();
        bool l = operands.top();
        operands.pop();
        operands.push(l|r);
    }

}

bool calculate_bool(const std::string &bool_eqw){
    std::stack <char> operators;
    std::stack <bool> operands;
    int id = 0, len = bool_eqw.length();
    for(int i = 0; i < len; i++){
        char cur = bool_eqw[i];
        if(cur == '0' || cur == '1')
            operands.push(cur == '1');
        else{
            if(cur == '(' || cur == '!')
                operators.push(cur);
            else if (cur == ')'){
                while(operators.top() != '('){
                    perform(operators.top(),operands);
                    operators.pop();
                }
                operators.pop();
            }
            else if (cur == '&'){
                if(!operators.empty()){
                    if(operators.top() == '|' || operators.top() == '(')
                        operators.push(cur);
                    else{
                        perform(operators.top(),operands);
                        operators.pop();
                        operators.push(cur);
                    }
                }
                else
                    operators.push(cur);
            }
            else if (cur == '|'){
                if(!operators.empty() &&  operators.top() != '('){
                    perform(operators.top(),operands);
                    operators.pop();
                }
                operators.push(cur);
            }
            else
                throw_error("Wrong operator: \"" + to_string(cur) + "\"");
        }
    }
    while(!operators.empty()){
        perform(operators.top(),operands);
        operators.pop();
    }

    return operands.top();
}

bool file_filter(std::string request, file* f){
    std::map <int, pair<int,std::string>> dict;

    std::string predicate = parse_string(request, dict);

    std::string bool_eqw =paste_predicate(f,predicate, dict);

    return calculate_bool(bool_eqw);
}




