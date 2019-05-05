#include <iostream>
#include <cctype>
#include <vector>
#include <cstdlib>
#include "vector_ls.h"
#include "array_ls.h"


struct Node{
    element* elem;
    Node* prev;
    Node* next;

    Node(std::string s){
        elem = new element(s);
        next = nullptr;
        prev = nullptr;
    }
};

std::string random_IP(){
    std::string s = "";
    for(int i = 0; i < 3; i++) {
        int a = rand() % 256;
        s += std::to_string(a);
        s += '.';
    }
    int a = rand() % 256;
    s += std::to_string(a);
    return s;
}

struct List{
    std::string name = "";
    int size = 0;
    Node* head;
};

List* create_empty_list(){
    int n, data;
    List* new_list = new List();
  //  std::cout << "Enter the name of new list: ";
  //  std::cin >> new_list->name;
  new_list->name = "Struct-list";
    new_list->head = nullptr;
    return new_list;
}

long long size_of_list(List* lst){
    return lst->size;
}


void print_cycled_list(List* lst, int starting = 1){
    if(starting == 1)
        std::cout << lst->name << ": \n";
    else
        std::cout << lst->name << " (Starting with number " << starting << "): \n";
    Node* cur_node = lst->head;
    for(int i = 1; i < starting; i++){
        cur_node = cur_node->next;
    }
    for(int i = 0, n = size_of_list(lst); i < n; i++){
        print_elem(cur_node->elem);
        cur_node = cur_node->next;
    }
    /* std::cout << "\nReversed: ";
     for(int i = 0, n = size_of_list(); i < n; i++){
         std::cout << "(" << cur_node->elem->data << ") ";
         cur_node = cur_node->prev;
     }*/
    std::cout << std::endl;
}

void delete_list(List* lst){
    Node* next_node;
    Node* cur_node = lst->head;
    cur_node->prev->next = nullptr;
    while(cur_node->next){
        next_node = cur_node->next;
        delete(cur_node->elem);
        delete(cur_node);
        cur_node = next_node;
    }
    delete(cur_node->elem);
    delete(cur_node);
    delete(lst);
}

void add_element_after_number(List* lst, std::string data, int number = 0){
    if(number > size_of_list(lst)){
        number = size_of_list(lst);
    }

    if(!check_valid(data)) {
        std::cout << "ERROR! IP adress is not valid. Could not create such node.\n";
        return;
    }

    Node* new_node = new Node(data);
    Node* cur_node = lst->head;

    if(size_of_list(lst) == 0){
        lst->head = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
        lst->size++;
        return;
    }

    if(number == 0){
        cur_node = cur_node->prev;
        new_node->next = cur_node->next;
        new_node->prev = cur_node;
        cur_node->next->prev = new_node;
        cur_node->next  = new_node;
        lst->head = new_node;

    }
    else{
        for(int i = 1; i < number; i++)
            cur_node = cur_node->next;
        new_node->next = cur_node->next;
        new_node->prev = cur_node;
        cur_node->next->prev = new_node;
        cur_node->next  = new_node;
    }
    lst->size++;
}

void get_element_by_id(List* lst, int number){
    while(number < 0) {number += lst->size;}
    if(lst->head == nullptr) {
        std::cout << "Nothing found, empty list.\n";
        return;
    }
    Node* cur_node = lst->head;
    if(number > lst->size){

    }
        number %= lst->size;
    for(int i = 1; i < number; i++) {
        cur_node = cur_node->next;
    }
    std::cout << "Node number " << number << " stores: ";
    print_elem(cur_node->elem);
}

void set_element(List* lst,  std::string value, int number){
    while(number < 0) {number += lst->size;}
    if(lst->size == 0)
        return;
    if(number > lst->size) {
        std::cout << "ERROR! Id you are trying to access is bigger than the size of your list!\n";
        std::cout << "Operation is being terminated.\n";
        return;
    }

    if(!check_valid(value)) {
        std::cout << "ERROR! IP adress is not valid. Could not create such node.\n";
        return;
    }

    Node* node = lst->head;
    for(int i = 1; i < number; i++) {
        node = node->next;
    }
    int it = 0, len = value.length();
    for(int i = 0; i < 4; i++){
        node->elem->data[i] = 0;
        do{
            node->elem->data[i] = node->elem->data[i]*10+(int)(value[it] - '0');
            it++;
        }while(it < len && value[it] != '.');
        it++;
    }
}

void delete_element_by_id(List* lst, int number){
    if(lst->size == 0){
        return;
    }
    if(number > lst->size){
        std::cout << "ERROR! Id you are trying to access is bigger than the size of your list!\n";
        std::cout << "Operation is being terminated.\n";
        return;
    }
    Node* cur_node = lst->head;

    for(int i = 1; i < number; i++) {
        cur_node = cur_node->next;
    }
    cur_node->next->prev = cur_node->prev;
    cur_node->prev->next  = cur_node->next;
    if(number == 1) lst->head = cur_node->next;
    delete(cur_node);
    lst->size--;
}

void interactive_list(List* root){
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
            default:
                std::cout << "No such command.\n";
                break;
        }
    }
}

void interactive(){
    std::cout << "Welcome to interactive mode!\n";
    std::string value;
    std::cout << "Firstly, choose, will the information be stored in:\n";
    std::cout << "a - a list of structures\n";
    std::cout << "b - std::vector\n";
    std::cout << "c - an array (amount of elements should be less than 50)\n";
    char mode;
    while(true){
        std::cout << "Your choise:";
        std::cin >> mode;
        if(mode == 'a' || mode == 'A') {
            List *root = create_empty_list();
            interactive_list(root);
            break;
        }
        else if(mode == 'b' || mode == 'B'){
            std::vector <element*> root = create_empty_vector();
            interactive_vector(root);
            break;
        }
        else if(mode == 'c' || mode == 'C'){
            element* *root = create_empty_array();
            interactive_array(root);
            break;
        }
        else
            std::cout << "Please try another command\n";
    }
}

void demo(){
    std::cout << "Welcome to demonstration mode!\n";
    List* root = create_empty_list();
    std::cout << "Adding element \"128.0.0.1\" at the head of the list\n";
    add_element_after_number(root,"128.0.0.1");
    std::cout << "Adding element \"1.1.1.1\" after number 1\n";
    add_element_after_number(root,"1.1.1.1",1);
    print_cycled_list(root);
    std::cout << "Adding element \"1.2.3.4\" at the head of the list\n";
    add_element_after_number(root,"1.2.3.4");
    print_cycled_list(root);
    std::cout << "Gettnig element by id = 2: ";
    get_element_by_id(root,2);
    std::cout << "Setting element with id = 2 to the value of \"2.4.8.16\" \n";
    set_element(root,"2.4.8.16",2);
    print_cycled_list(root);
    print_cycled_list(root,2);
    std::cout << "Deleting element with id = 1\n";
    delete_element_by_id(root,1);
    print_cycled_list(root);
    delete_list(root);
}

void benchmark() {

    std::cout << "Rewriting \"benchmark.txt\"...\n";
    freopen("benchmark.txt","w",stdout);
    std::cout << "Results for list:\n";
    List* lst = create_empty_list();
    double diff = 0.0;
        long long cnt_for_sec = 1;
        auto bench_clock = clock();

       while(diff < 2) {
            cnt_for_sec = cnt_for_sec<<1;
            bench_clock = clock();
            for (int i = 0; i < cnt_for_sec; i++) {
                add_element_after_number(lst, random_IP());
            }
            diff = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;
            std::cout << cnt_for_sec << ":" << diff << "\n";
        }
        std::cout << "Deleting...\n";
        cnt_for_sec = 1;
        diff=  0;
        while(diff < 2 && size_of_list(lst) > 0) {
            cnt_for_sec = cnt_for_sec<<1;
            bench_clock = clock();
            for (int i = 0; i < cnt_for_sec; i++) {
                delete_element_by_id(lst, rand() %(size_of_list(lst)));
            }
            diff = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;
            for (int i = 0; i < cnt_for_sec; i++) {
                add_element_after_number(lst, random_IP());
            }
            std::cout << cnt_for_sec << ":" << diff << "\n";
        }

    std::cout << "Results for std::vector:\n";
    std::vector <element*> vec = create_empty_vector();
    diff = 0.0;
    cnt_for_sec = 1;

    while(diff < 2) {
        cnt_for_sec = cnt_for_sec<<1;
        bench_clock = clock();
        for (int i = 0; i < cnt_for_sec; i++) {
            add_element_after_number(vec, random_IP());
        }
        diff = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;
        std::cout << cnt_for_sec << ":" << diff << "\n";
    }
    std::cout << "Deleting...\n";
    cnt_for_sec = 1;
    diff=  0;
    while(diff < 2 && size_of_list(vec) > 0) {
        cnt_for_sec = cnt_for_sec<<1;
        bench_clock = clock();
        for (int i = 0; i < cnt_for_sec; i++) {
            delete_element_by_id(vec, 1);
        }
        diff = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;
        for (int i = 0; i < cnt_for_sec; i++) {
            add_element_after_number(lst, random_IP());
        }
        std::cout << cnt_for_sec << ":" << diff << "\n";
    }

    std::cout << "Results for array:\n";
    element** arr = create_empty_array();
    diff = 0.0;
    cnt_for_sec = 1;

    while(diff < 2) {
        cnt_for_sec = cnt_for_sec<<1;
        bench_clock = clock();
        for (int i = 0; i < cnt_for_sec; i++) {
            add_element_after_number(arr, random_IP(),1);
        }
        diff = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;
        std::cout << cnt_for_sec << ":" << diff << "\n";
    }
    std::cout << "Deleting...\n";
    cnt_for_sec = 1;
    diff=  0;
    while(diff < 2){// && size_of_list(arr) > 0) {
        cnt_for_sec = cnt_for_sec<<1;
        bench_clock = clock();
        for (int i = 0; i < cnt_for_sec && size_of_list(arr) > 0; i++) {
            delete_element_by_id(arr, 1);
        }
        diff = (double) (clock() - bench_clock) / CLOCKS_PER_SEC;
        if(size_of_list(arr) > 0)
            for (int i = 0; i < cnt_for_sec; i++) {
                add_element_after_number(arr, random_IP());
            }
        std::cout << cnt_for_sec << ":" << diff << size_of_list(arr) << "\n";
    }

    std::cout << "E.N.D.\n";
   // fclose(stdout);
   delete_list(arr);
    std::cout << "Yeah!\n";
}


int main() {
    while(true) {
        int key;
        std::cout << "MAIN MENU\n";
        std::cout << "Please, choose your mode:\n";
        std::cout << "Press 1 for interactive mode.\n";
        std::cout << "Press 2 for demonstration mode.\n";
        std::cout << "Press 3 for benchmark mode.\n";
        std::cout << "Press 4 to exit the program\n";
        std::cin >> key;
        switch(key){
            case 1:
                interactive();
                return 0;
            case 2:
                demo();
                break;
            case 3:
                benchmark();
                return 0;
                break;
            case 4:
                return 0;
            default:
                std::cout << "Try another command!\n";

        }
    }
}