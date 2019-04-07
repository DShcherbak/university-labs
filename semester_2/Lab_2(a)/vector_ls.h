//
// Created by sadoffnick on 05.04.19.
//
#pragma once
#ifndef UNIVERSOTY_LAB2_VECTOR_LS_H
#define UNIVERSOTY_LAB2_VECTOR_LS_H
#include <iostream>
#include <cctype>
#include <vector>


int new_digit(std::string s, int &i){
    int res = 0;
    while( i < s.length() && isdigit(s[i])){
        res = res*10 + (int)(s[i] - '0');
        i++;
    }
    return res;
}

bool check_valid(std::string s){
    int i = 0;
    int a = 0;
    while (s[i] == ' ') i++;
    if(s[i] == '.') return false;
    for(int id = 0; id < 3; id++) {
        a = new_digit(s, i);
        if (a < 0 || a > 255) return false;
        if (s[i] != '.') return false;
        i++;
    }
    a = new_digit(s, i);
    if (a < 0 || a > 255) return false;
    while(i < s.length() && s[i] == ' ') i++;
    if(i < s.length()) return false;
    return true;
}


struct element{
    int data[4];

    element(std::string s){
        int it = 0;
        for(int i = 0; i < 3; i++) {
            data[i] = new_digit(s, it);
            it++;
        }
        data[3] = new_digit(s, it);
    }
};

long long size_of_list(std::vector <element*> lst){
    return lst.size();
}

void print_elem(element* elem){
    std::cout << "(" << elem->data[0] <<"." << elem->data[1] << '.' << elem->data[2] << '.' << elem->data[3]<< ")\n";
}



std::vector <element*> create_empty_vector(){
    int n, data;
    std::vector <element*> new_list;
    return new_list;
}

void print_cycled_list(std::vector <element*> lst, int starting = 1){
    if(starting == 1)
        std::cout << "Vector-list: \n";
    else
        std::cout << "Vector-list (Starting with number " << starting << "): \n";

    for(int i = starting-1; i < lst.size(); i++){
        print_elem(lst[i]);
    }
    for(int i = 0; i < starting-1; i++)
        print_elem(lst[i]);
    std::cout << std::endl;
}

void delete_list(std::vector <element*> lst){
    for(auto e : lst)
        delete(e);
}

void add_element_after_number(std::vector <element*> &lst, std::string data, int number = 0){
    if(number > lst.size()){
        number = lst.size();
    }

    if(!check_valid(data)) {
        std::cout << "ERROR! IP adress is not valid. Could not create such node.\n";
        return;
    }

    element* new_elem = new element(data);

    if(lst.size() == 0){
        lst.push_back(new_elem);
        print_cycled_list(lst);
        return;
    }
    element* cur = lst[lst.size()-1];
    lst.push_back(cur);
    for(int i = lst.size()-2; i > number; i--){
        lst[i] = lst[i-1];
    }
    lst[number] = new_elem;

}

void get_element_by_id(std::vector <element*> lst, int number){

    std::cout << "Node number " << number << " stores: ";
    number--;
    print_elem(lst[number]);
}

void set_element(std::vector <element*> lst,  std::string value, int number){
    if(lst.size() == 0)
        return;
    number--;
    if(number > lst.size()) {
        std::cout << "ERROR! Id you are trying to access is bigger than the size of your list!\n";
        std::cout << "Operation is being terminated.\n";
        return;
    }

    if(!check_valid(value)) {
        std::cout << "ERROR! IP adress is not valid. Could not create such node.\n";
        return;
    }


    int it = 0, len = value.length();
    for(int i = 0; i < 3; i++) {
        lst[number]->data[i] = new_digit(value, it);
        it++;
    }
    lst[number]->data[3] = new_digit(value, it);
}

void delete_element_by_id(std::vector <element*> &lst, int number){
    if(lst.size() == 0){
        return;
    }
    number--;
    if(number > lst.size()){
        std::cout << "ERROR! Id you are trying to access is bigger than the size of your list!\n";
        std::cout << "Operation is being terminated.\n";
        return;
    }

    for(int i = number; i < lst.size()-1; i++) {
        lst[i]  = lst[i+1];

    }
    lst.pop_back();
}

void interactive_vector(std::vector <element*> root){
    char key; int ID; std::string value;
    while(true){

        std::cout << "Here's list of your options:\n";
        std::cout << "Enter \"a\" to add an element after custom position to the list (enter it's value and position)\n";
        std::cout << "Enter \"d\" to delete an element by it's position\n";
        std::cout << "Enter \"g\" to get element value by it's position\n";
        std::cout << "Enter \"s\" to set element value by it's position\n";
        std::cout << "Enter \"p\" to print the list starting with some position\n";
        std::cout << "Enter \"q\" to quit.\n";
        char key;
        std::cin >> key;

        if(key == 'q'){
            std::cout << "Good bye!\n";
            delete_list(root);
            return;
        }

        if(key == 'a' || key == 's'){
            std::cout << "Enter value:\n";
            std::cin >> value;
        }
        std::cout << "Enter position:\n";
        std::cin >> ID;

        switch(key){
            case 'a':
                add_element_after_number(root,value,ID);
                break;
            case 'd':
                delete_element_by_id(root,ID);
                break;
            case 'g':
                get_element_by_id(root,ID);
                break;
            case 's':
                set_element(root,value, ID);
                break;
            case 'p':
                print_cycled_list(root,ID);
                break;
            case 'q':
                std::cout << "Good bye!\n";
                delete_list(root);
                return;
            default: std::cout << "No such command.\n";
                break;
        }
    }
}

#endif //UNIVERSOTY_LAB2_VECTOR_LS_H
