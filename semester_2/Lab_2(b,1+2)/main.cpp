#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

struct Node{
    int value;
    Node* next;

    Node(int v, Node* n){
        value = v;
        next = n;
    }
};

struct List{
    Node* head;
    string name;
    int size = 0;

    List(Node* h = nullptr, int s = 0, string _name = "List number"){
        head = h;
        size = s;
        name = _name;
    }
};

int random_value(){
    return rand()%10000;
}

Node* create_node_random(){
    int value = random_value();
    Node* new_node = new Node(value,nullptr);
    return new_node;
}

void add_node_to_list(List* lst, Node* n){
    Node* cur_node = lst->head;
    lst->size++;
    if(cur_node == nullptr){
        lst->head = n;
        n->next = n;
        return;
    }

    cur_node = cur_node->next;
    while(cur_node->next != lst->head) cur_node = cur_node->next;
    cur_node->next = n;
    n->next = lst->head;
}

void add_value_to_list(List* lst, int value){
    Node* new_node = new Node(value,nullptr);
    add_node_to_list(lst, new_node);
}

void print_list(List* lst){
    std::cout << lst->name;
    std::cout << ": \n";
    Node* cur_node = lst->head;
    for(int i = 0, n = lst->size; i < n; i++){
        std::cout << cur_node->value;
        cur_node = cur_node->next;
    }
    std::cout << std::endl;
}

void delete_list(List* lst){
    Node* next_node;
    Node* cur_node = lst->head;
    if(lst->head == nullptr){
        delete(lst);
        return;
    }
    for(int i = 0, n = lst->size-1; i < n; i++){
        next_node = cur_node->next;
        delete(cur_node);
        cur_node = next_node;
    }
    delete(cur_node);
    delete(lst);
}

List* slice(List* lst, int st, int end, int step = 1){
    if(st < 0 && end < 0){
	st+=lst->size;
	end+=lst->size;
    }
    if(st >= 0 && end >=0){  
    	List* new_list = new List();
    	Node* cur_node = lst->head;
	for(int i = 0; i < st; i++){
	    std::cout << cur_node->value;
	    cur_node = cur_node->next;
        }
    	int st = 0;
	for(int i = st; i < end; i++){
	    if(st == 0) add_node_to_list(new_list, cur_node);
	    st++;
		st%=step;
	}
    }
    return new_list;
}

int main(){

    return 0;
}
