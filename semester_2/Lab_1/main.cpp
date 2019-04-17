#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>


using namespace std;

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
    void set_time(){
        time_t now = time(nullptr);
        tm *gmtm = gmtime(&now);
        cur_time = convert_time(gmtm);
       // delete(gmtm);
    }
    void set_author(int cur_id){
        author_id = cur_id;
    }

    void set_adress(int adr){
        adress_id = adr;
    }

    void get_message(int current_login, int adr, std::string T = ""){
        if(T.empty())
            cin >> T;
        set_text(T);
        set_time();
        set_author(current_login);
        set_adress(adr);
    }
    
    void print(const std::string &author_name){
        std::cout << author_name << ": " << text;
    }



};

class server{
private:

public:
    vector <message> messages;
    vector <std::string> name;
    std::map <std::string, std::string> password;
    std::map <std::string, std::string> id;
    std::set <std::string> logins;

    void load() {
        freopen("passwords","r",stdin);
        int cnt_users = 0, _id;
        std::string login, pass;
        cin >> cnt_users;
        for(int i = 0; i < cnt_users; i++){
            cin >> _id >> login >> pass;
            name.push_back(login);
            password[login] = pass;
            id[login] = _id;
            logins.insert(login);
        }
        messages.resize(3);
        messages[0].get_message(0,1, "Hello!");
        messages[1].get_message(0,1, "dear admin");
        messages[2].get_message(0,1, "i love you!");
        cout << "Server loaded!\n";

    }

    void sign_up(string log){
        std::cout << "Your password:";
    }
};

std::string convert_month(int n){
    if (n < 9)
        return ('0' + to_string(n+1));
    else
        return to_string(n+1);

}

std::string convert_time(tm* t){
    std::string current_time = "";
    current_time += to_string((*t).tm_hour+2) +':'+ to_string((*t).tm_min) +':'+ to_string((*t).tm_sec);
    current_time += " ";
    current_time += to_string((*t).tm_mday) +'.'+ convert_month((*t).tm_mon) +'.'+ to_string((*t).tm_year+1900);
    return current_time;
}



int main() {
    server S;
    S = *(new server());
    S.load();
    //log_in
    message new_message;
//    new_message.get_message(1,0);
//    new_message.print(S.name[1]);
    bool logged_in = false;
    std::string log;
    char q;
    while(!logged_in){
        std::cout << "Please, log in to use my messager.\nYour login: ";
        cin >> log;
        if(S.logins.count(log) == 0){
            std::cout << "No such user found. Would you like to sign up? (y/n)";
            std :: cin >> q;
            if(q == 'y' || q == 'Y')
            {
                S.sign_up(log);
            }
        }
    }

}