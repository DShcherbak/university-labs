//
// Created by sadoffnick on 13.06.19.
//
#pragma once
#include <iostream>
#include "List.h"
#include "element.h"

struct Node{
    element* elem;
    Node* next;

    Node(element* e){
        elem = e;
        next = nullptr;
    }
};

List* List::create_empty(){
    List* lst = new List();
    lst->head = nullptr;
    return lst;
}

void List::add_node(Node* new_node){
    if(head == nullptr){
        head = new_node;
        head->next = nullptr;
        return;
    }
    Node* cur = head;
    while(cur->next != nullptr){
        cur = cur->next;
    }
    cur->next = new_node;
}

void List::delete_element(int value) {
    Node* cur = head;
    while(head && head->elem->val == value){
        cur = head;
        head = head->next;
        delete cur;
    }
    Node* next = head->next;
    while(next){
        if(next->elem->val == value){
            cur->next = next->next;
            delete next;
            next = cur->next;
        }
        else{
            cur = next;
            next = next->next;
        }
    }
}

void List::add_element(int value){
    element* elem = new element(value);
    Node* new_node = new Node(elem);
    List::add_node(new_node);

}

int List::find_by_range(int st,int fin) {
    int cnt = 0;
    Node* cur = head;
    while(cur){
        if(cur->elem->val >= st && cur->elem->val <= fin)
            cnt++;
        cur = cur->next;
    }
    return cnt;
}

void List::print(){
    int cnt = 0;
    Node* cur = head;
    while(cur){
        std::cout << cur->elem->val;
        if(cur->next)
            std::cout << " -> ";
        else
            std::cout << ".\n";
        cur = cur->next;
    }
}
