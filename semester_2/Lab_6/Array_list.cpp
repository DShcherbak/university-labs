
#pragma once
#ifndef UNIVERSOTY_LAB2_ARRAY_LS_H
#define UNIVERSOTY_LAB2_ARRAY_LS_H
#include <iostream>
#include <cctype>
#include "element.h"
#include "Array_list.h"
//using namespace std;


Array_list* Array_list::create_empty(){
    int n, data;
    Array_list* new_list = new Array_list;
    for(int i = 0; i < MAXSIZE; i++){
        new_list->elems[i] = nullptr;
    }
    return new_list;
}


long long size_of_list(Array_list* lst){
    int size  = 0;
    while(size < MAXSIZE && lst->elems[size] != nullptr) size++;
    return size;
}

void Array_list::print(){
    std::cout << "Array-list: \n";
    long long size = size_of_list(this);
    int cnt = 0;
    if(size == 0){
        std::cout << "Empty.\n";
        return;
    }
    for(int i = 0; i < size-1; i++){
        std::cout << elems[i]->val << " -> ";
    }
    std::cout << elems[size-1]->val << ".\n";
}


void Array_list::add_element(int data){
    int number = 0;
    for(;number < MAXSIZE && elems[number]; number++);
    if(number == MAXSIZE){
        std::cout << "ERROR! Stack overflow.\n";
        std::cout << "Operation is being terminated.\n";
        return;
    }
    elems[number] = new element(data);
}



void Array_list::delete_element(int value){
    long long size = size_of_list(this);
    if(size == 0){
        return;
    }
    int cur_id = 0;
    int next_id = 0;
    while(elems[next_id]){
        while(next_id < size && elems[next_id]->val == value){
            next_id++;
        }
        elems[cur_id] = elems[next_id];
        cur_id++;
        next_id++;
    }
}


int Array_list::find_by_range(int st, int fin) {
    long long size = size_of_list(this);
    int cnt = 0;
    for(int i = 0; i < size; i++){
        if((elems[i]->val >= st) && (elems[i]->val <= fin))
            cnt++;
    }
   return cnt;
}




#endif //UNIVERSOTY_LAB2_ARRAY_LS_H
