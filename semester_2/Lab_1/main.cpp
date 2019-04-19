#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>


std::string convert_month(int n);

std::string convert_time(tm* t);

class message{
private:
    std::string text = "";
    std::string cur_time;
    int author_id;
    int adress_id;

public:
    void set_text(std::string T){
        text = T;
    }
    std::string get_text(){
        return text;
    }
    void set_time(){
        time_t now = time(nullptr);
        tm *gmtm = gmtime(&now);
        cur_time = convert_time(gmtm);
       // delete(gmtm);
    }
    std::string get_time(){
        return cur_time;
    }
    void set_author(int cur_id){
        author_id = cur_id;
    }
    int get_author(){
        return author_id;
    }
    void set_adress(int adr){
        adress_id = adr;
    }
    int get_adress(){
        return adress_id;
    }
    void get_message(int aut, int adr, std::string T){
        set_text(T);
        set_time();
        set_author(aut);
        set_adress(adr);
    }
    void print(const std::string &author_name){
        std::cout << author_name << ": " << text << " :: " << cur_time << "\n";
    }
    std::string transform(){
        std::string res = "";
        res += std::to_string(author_id) + "\n";
        res += std::to_string(adress_id) + "\n";
        res += text + "\n";
        res += cur_time + "\n";
        return res;
    }
};

class server{
private:
    int CNT_USERS = 1;

public:
    std::vector <message> messages;
    std::vector <std::string> name;
    std::map <std::string, int> id;
    std::set <std::string> names;

    void load() {
        messages.resize(3);
        messages[0].get_message(0,1, "Hello!");
        messages[1].get_message(0,1, "dear admin");
        messages[2].get_message(0,1, "i love you!");
        name.push_back("Admin");
        name.push_back("Test");
        std::cout << "Server loaded!\n";

    }

    void save() {
        FILE* back = fopen("backup.txt","r");
        std::string mes;
        mes = messages[0].transform();
        std::cout << "mama\n";
        //for(auto m : messages){
         //   mes = m.transform();
         //   fprintf(back,"%s", &mes);
        //std::cout << "iamere\n";
        //}
        fclose(back);
        std ::cout << "All saved!\n";
    }

    void print(int from = 0, int to = 0){
        if(from == 0 && to == 0){
            for(auto m : messages){
                m.print(name[m.get_author()]);
            }
        }
        else{
            for(auto m : messages){
                if((from == m.get_author() || from == 0) && (to == m.get_adress() || to == 0))
                    m.print(name[m.get_author()]);
            }
        }
    }

    void add_message(message m){
        messages.push_back(m);
    }

    void new_message(){
        std::string author, adress, Text;
        std::cout << "Enter your name:\n";
        getline(std::cin, author);
        std::cout << "Whom is your message for:\n";
        getline(std::cin, adress);
        std::cout << "Enter your message:\n";
        getline(std::cin, Text);
        message m;
        if(names.count(author) == 0){
            id[author] = ++CNT_USERS;
            names.insert(author);
            name.push_back(author);

        }
        if(names.count(adress) == 0){
            id[adress] = ++CNT_USERS;
            names.insert(adress);
            name.push_back(adress);
        }
        m.get_message(id[author],id[adress],Text);
        add_message(m);
    }
};

std::string convert_month(int n){
    if (n < 9)
        return ('0' + std::to_string(n+1));
    else
        return std::to_string(n+1);

}

std::string convert_time(tm* t){
    std::string current_time = "";
    current_time += std::to_string((*t).tm_hour+2) +':'+ std::to_string((*t).tm_min) +':'+ std::to_string((*t).tm_sec);
    current_time += " ";
    current_time += std::to_string((*t).tm_mday) +'.'+ convert_month((*t).tm_mon) +'.'+ std::to_string((*t).tm_year+1900);
    return current_time;
}

/*
void interactive(){
    char key; int ID; std::string value;
    server S;
    S = *(new server());
    S.load();
    while(true){
        std::cout << "Here's list of your options:\n";
        std::cout << "Enter \"n\" to add a new message\n";
        std::cout << "Enter \"s\" to save current state to file\n";
        std::cout << "Enter \"l\" to load messages from file (be careful, all unsaved changes will be lost!)\n";
        std::cout << "Enter \"p\" to print messages\n";
        std::cout << "Enter \"f\" to find some messages\n";
        std::cout << "Enter \"q\" to quit.\n";
        std::cin >> key;
        if(key == 'q'){
            std::cout << "Good bye!\n";
            return;
        }
        switch(key){
            case 'n':
                S.new_message();
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
*/

void demo() {
    server S;
    S = *(new server());
    S.load();
    //log_in
   // S.new_message();
   // S.print();
    S.save();
    // new_message.get_message(1,0,T);
    //new_message.print(S.name[1]);
    //  S.add_message(new_message);


}

void benchmark() {

    std::cout << "Rewriting \"benchmark.txt\"...\n";
    //  freopen("benchmark.txt","w",stdout);

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
//            case 1:
  //              interactive();
   //             return 0;
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