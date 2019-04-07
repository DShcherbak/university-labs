#include <iostream>
#include <cctype>
#include <set>
#include <map>

struct Node{
    long long value;
    Node* next;

    Node(int v){
        value = v;
        next = nullptr;
    }
};

struct stack{
    Node* top;
    int max_size = 1e7;
    int size;

    stack(){
        size = 0;
        top = nullptr;
    }

    void push(std::string s){
        int value = 0;
        for(int i = 0, l = s.length(); i < l; i++)
            value = value*10+ (int)(s[i] - '0');
        Node* new_node = new Node(value);
        new_node->next = top;
        top = new_node;
    }

    void push(int value){
        Node* new_node = new Node(value);
        new_node->next = top;
        top = new_node;
    }

    int peek(){
        std::cout << top->value;
    }
    int pop(){
        int res = top->value;
        top = top->next;
        return res;
    }

    void print(){
        Node* cur = top;
        std::cout << "Stack: ";
        if(cur == nullptr){
            std::cout << "Empty.\n";
            return;
        }
        while(cur != nullptr){
            std::cout << cur->value << " ";
            cur = cur->next;
        }
        std::cout << "\n";
    }
};

bool is_valid_int(std::string s){
    for(int i = 0, l = s.length(); i < l; i++)
        if(!isdigit(s[i]))
            return false;
        return true;

}

bool str_pick(std::string s, int &id){
    if((s[id] == 'p' || s[id] == 'P') &&
         (s[id+1] == 'i' || s[id+1] == 'I') &&
            (s[id+2] == 'c' || s[id+2] == 'C') &&
                (s[id+3] == 'k' || s[id+3] == 'K')){
        id+=4;
        return true;
    }
    return false;
}

bool str_roll(std::string s, int &id){
    if((s[id] == 'r' || s[id] == 'R') &&
       (s[id+1] == 'o' || s[id+1] == 'O') &&
       (s[id+2] == 'l' || s[id+2] == 'L') &&
       (s[id+3] == 'l' || s[id+3] == 'L')){
            id+=4;
            return true;
    }
    return false;
}

void pick(int n, stack* stk){
    if(n >= stk->size) {
        std::cout << "ERROR! Not enough elements in stack.\n";
        return;
    }
    Node* cur_node = stk->top;
    for(int dep = 0; dep < n; dep++){
        cur_node = cur_node->next;
    }
    Node* new_node = new Node(cur_node->value);
    new_node->next = stk->top;
    stk->top = new_node;
    stk->size++;
}

void roll(int n, stack* stk){
    if(n >= stk->size) {
        std::cout << "ERROR! Not enough elements in stack.\n";
        return;
    }

    Node* cur_node = stk->top;
    for(int dep = 0; dep < n-1; dep++){
        cur_node = cur_node->next;
    }
    Node* tmp_node = cur_node->next->next;
    cur_node->next->next = stk->top;
    stk->top = cur_node->next;
    cur_node->next = tmp_node;
}

void operate(stack* stk, std::string op, std::map <std::string, std::string> operations){
    op = operations[op];
    if(op == "." || op == ".\n"){
        stk->peek();
        return;
    }
    long long a = stk->pop();
    long long b;
    int i = 0;
    int l = op.length();
    while(i < l){ //   for(int i = 0, l = op.length(); i < l; i++){
        if(op[i] == ' ') {i++; continue;}
        if(str_pick(op,i)){
            pick(a, stk);
            a = stk->pop();
            continue;
        }
        if(str_roll(op,i)){
            roll(a, stk);
            stk->print();
            a = stk->pop();
            continue;
        }
        b = stk->pop();
        std::cout << a << " " << op[i] << " " << b << std::endl;
        if(op[i] == '+')
            a += b;
        else if(op[i] == '-')
            a -= b;
        else if(op[i] == '*')
            a *= b;
        else if(op[i] == '/')
            a /= b;
        else if(op[i] == '%')
            a %= b;
        else if(op[i] == '.')
            stk->peek();
        i++;
        std::cout << a << "is put on top of the stack.\n";
    }

    stk->push(a);
    stk->print();
}

std::string new_word(std::string s, int &id){
    std::string res = "";
    int n = s.length();
    while(s[id] == ' ' && id < n) id++;
    while(s[id] != ' ' && id < n){
        if(s[id] != ';')
            res += s[id];
        id++;
    }
    return res;
}

void add_operator(std::set <std::string> &operators, std::map <std::string, std::string> &operations, std::string key, std::string value){
    bool add = true;
    if(operators.count(key)){
        std::cout << "Such operator alrady exists. Do you wish to change its value? (y/n) \n";
        char ans;
        std::cin >> ans;
        if (ans == 'n' || ans == 'N') add = false;
    }
    if(add){
        operators.insert(key);
        operations[key] = value;
    }
}

void add_new_operator(std::set <std::string> &operators, std::map <std::string, std::string> &operations, std::string s){
    std::string key = "", value = "", word = "";
    int id = 0, len = s.length();
    key = new_word(s,id);
    while(id < len) {
        word = new_word(s, id);
        if (operators.count(word))
            word = operations[word];
        value += word;
    }
    std::cout << "New operator \"" << key << "\" is equal to \"" << value << "\"\n";
    add_operator(operators,operations,key,value);
}

void delete_stack(stack* stk){
    Node* cur_node = stk->top;
    for(int i = 0, n = stk->size; i < n; i++){
        cur_node = stk->top->next;
        delete(stk->top);
        stk->top = cur_node;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::set <std::string> operators;
    std::map <std::string, std::string> operations;
    add_operator(operators, operations, ".", ".");
    add_operator(operators, operations, "+", "+");
    add_operator(operators, operations, "-", "-");
    add_operator(operators, operations, "*", "*");
    add_operator(operators, operations, "/", "/");
    add_operator(operators, operations, "%", "%");
    add_operator(operators, operations, "PICK", "PICK");
    add_operator(operators, operations, "ROLL", "ROLL");

    Node* n = new Node(5);
    std::cout << n->value*n->value << std::endl;
    std::string s,q;
    stack* stk = new stack();
    while(std::cin >> s){
        if(is_valid_int(s)){
            stk->push(s);
            stk->size++;
        }
        else if(operators.count(s)){
            operate(stk,s,operations);
        }
        else if (s == "quit"){
            break;
        }
        else{
            std::cout << "Unknown operator found. It will be created. It will consist of another operators existing.\n";
            std::cout << "Enter ';' to mark the end of your operator\n";
            while(std::cin >> q){
                if(q[q.length()-1] == ';')
                    break;
                s = s + " " + q;
            }
            if(q != ";")
                s = s + " " + q;
            add_new_operator(operators, operations, s);
        }

    }
    delete_stack(stk);
    return 0;
}