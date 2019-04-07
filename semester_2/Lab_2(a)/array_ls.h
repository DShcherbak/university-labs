//
// Created by sadoffnick on 05.04.19.
//
#pragma once
#ifndef UNIVERSOTY_LAB2_ARRAY_LS_H
#define UNIVERSOTY_LAB2_ARRAY_LS_H
#include <iostream>
#include <cctype>
#include "vector_ls.h"
//using namespace std;

const int MAXSIZE = 1048576;


element**  create_empty_array(){
    int n, data;
    element** new_list = new element*[MAXSIZE];
    for(int i = 0; i < MAXSIZE; i++){
        new_list[i] = nullptr;
    }
    return new_list;
}


long long size_of_list(element** lst){
    int size  = 0;
    while(size < MAXSIZE && lst[size] != nullptr) size++;
    return size;
}

void print_cycled_list(element** lst, int starting = 1){
    if(starting == 1)
        std::cout << "Array-list: \n";
    else
        std::cout << "Array-list (Starting with number " << starting << "): \n";

    for(int i = starting-1; lst[i] != nullptr; i++){
        print_elem(lst[i]);
    }
    for(int i = 0; i < starting-1; i++)
        print_elem(lst[i]);
    std::cout << std::endl;
}

void delete_list(element** lst){
    delete(lst);
}

void add_element_after_number(element** lst, std::string data, int number = 0){
    if(number > MAXSIZE){
        std::cout << "ERROR! Id you are trying to access is bigger than the size of your list!\n";
        std::cout << "Operation is being terminated.\n";
        return;
    }

    if(!check_valid(data)) {
        std::cout << "ERROR! IP adress is not valid. Could not create such node.\n";
        return;
    }
    element* new_elem = new element(data);

    if(lst[0] == nullptr){
        lst[0] = new_elem;
        return;
    }
    int size = size_of_list(lst);
    if(number > size) number = size;
    if(size >= MAXSIZE) {
            std::cout << "ERROR! Your array is overflown. Please delete elements in order to add another.\n";
            std::cout << "Operation is being terminated.\n";
            return;
        }
    for(int i = size; i > number; i--){
        lst[i] = lst[i-1];
    }
    lst[number] = new_elem;

}

void get_element_by_id(element** lst, int number){

    std::cout << "Node number " << number << " stores: ";
    number--;
    print_elem(lst[number]);
}

void set_element(element** lst,  std::string value, int number){
    long long size = size_of_list(lst);
    if(size == 0)
        return;
    number--;
    if(number > size) {
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

void delete_element_by_id(element** lst, int number){
    long long size = size_of_list(lst);
    if(size == 0){
        return;
    }
    number--;
    if(number > size){
        std::cout << "ERROR! Id you are trying to access is bigger than the size of your list!\n";
        std::cout << "Operation is being terminated.\n";
        return;
    }
    delete(lst[number]);
 //   std::cout << size << ".|\n";
    for(int i = number; i < size-2; i++) {
        lst[i]  = lst[i+1];

    }
    lst[size-1] = nullptr;
}

void interactive_array(element** root){
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


#endif //UNIVERSOTY_LAB2_ARRAY_LS_H
