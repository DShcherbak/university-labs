#include <iostream>
#include <cctype>
//using namespace std;

const int MAXSIZE = 50;


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

void print_elem(element* elem){
    std::cout << "(" << elem->data[0] <<"." << elem->data[1] << '.' << elem->data[2] << '.' << elem->data[3]<< ")\n";
}



element**  create_empty(){
    int n, data;
    element** new_list = new element*[MAXSIZE];
    for(int i = 0; i < MAXSIZE; i++){
        new_list[i] = nullptr;
    }
    return new_list;
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
    for(int i = 0; i < MAXSIZE; i++){
        delete(lst[i]);
    }
}

void add_element_after_number(element** lst, std::string data, int number = 0){
/*    if(number > lst.size()){
        std::cout << "ERROR! Id you are trying to access is bigger than the size of your list!\n";
        std::cout << "Funcition is being terminated.\n";
        return;
    }
*/
    if(!check_valid(data)) {
        std::cout << "ERROR! IP adress is not valid. Could not create such node.\n";
        return;
    }

    element* new_elem = new element(data);

    if(lst[0] == nullptr){
        lst[0] = new_elem;
        return;
    }
    int size  = 0;
    while(lst[size] != nullptr) size++;
    element* cur = lst[size-1];
    lst[size] = cur;
    for(int i = size-2; i > number; i--){
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
    int size  = 0;
    while(lst[size] != nullptr) size++;
    if(size == 0)
        return;
    number--;
    if(number > size) {
        std::cout << "ERROR! Id you are trying to access is bigger than the size of your list!\n";
        std::cout << "Funcition is being terminated.\n";
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
    int size  = 0;
    while(lst[size] != nullptr) size++;
    if(size == 0){
        return;
    }
    number--;
    if(number > size){
        std::cout << "ERROR! Id you are trying to access is bigger than the size of your list!\n";
        std::cout << "Funcition is being terminated.\n";
        return;
    }

    for(int i = number; i < size-1; i++) {
        lst[i]  = lst[i+1];

    }
    delete(lst[size-1]);
    lst[size-1] = nullptr;
}

