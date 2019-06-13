#include <iostream>
#include "element.h"
#include "List.h"
#include "Array_list.h"
#include "Binary_tree.h"


template <class T> class Holder{
public:

    T* Tree;
    int type;

    Holder(){
        Tree = new T;
        type = 1;
    }

    void create_empty(){
        Tree = Tree->create_empty();
    }

    void add_element(int value){
        Tree->add_element(value);
    }

    void delete_element(int value){
        Tree->delete_element(value);
    }

    void find_by_value(int value){
        std::cout << "Number of value = " << value << " elements is: " << Tree->find_by_range(value,value) << "\n";
    }

    void find_by_range(int st, int fin){
        std::cout << "Number of elements with value in [" << st << ";" << fin << "] is : " << Tree->find_by_range(st,fin) << "\n";
    }

    void print(){
        Tree->print();
    }
};

template<class T>
void demo(T* a){
    Holder <T> Lst;
    Lst.create_empty();
    Lst.add_element(5);
    Lst.add_element(12);
    Lst.add_element(999);
    Lst.print();
    Lst.add_element(12);
    Lst.add_element(54);
    Lst.print();
    Lst.find_by_value(12);
    Lst.find_by_range(12,55);
    Lst.add_element(5);
    Lst.add_element(5);
    Lst.print();
    Lst.delete_element(5);
    Lst.print();
}

int main() {
    int key;
    while(true) {
        std::cout << "MAIN MENU\n";
        std::cout << "Please, choose your mode:\n";
        std::cout << "Press 1 to use List.\n";
        std::cout << "Press 2 to use Array list.\n";
        std::cout << "Press 3 to use Binary tree.\n";
        std::cout << "Press 4 to exit the program\n";
        std::cin >> key;
        switch(key){
            case 1:
                List* L;
                demo(L);
                return 0;
            case 2:
                Array_list* A;
                demo(A);
                return 0;
            case 3:
                Binary_tree* B;
                demo(B);
                return 0;
            case 4:
                std::cout << "Bye-bye!\n";
                return 0;
            default:
                std::cout << "Try another command!\n";
        }
    }
}