#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

string convert_month(int n);

string convert_time(tm* t);

class message{
private:
    string text = "";
    string cur_time;
    int author_id;
    int adress_id;
public:
    void set_text(string T){
        text = T;
    }
    void set_time(){
        time_t now = time(0);
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

    void get_message(int current_login, int adr, string T = ""){
        if(T == "")
            cin >> T;
        set_text(T);
        set_time();
        set_author(current_login);
        set_adress(adr);
    }



};

class server{
private:
    vector <message> messages;
public:
    void load() {
       // freopen("backup.txt","r",stdin);
        // TODO : Розібратись як с.ка нормально читати з файла базу данних
        messages.resize(3);
        messages[0].get_message(0,1, "Hello!");
        messages[1].get_message(0,1, "dear admin");
        messages[2].get_message(0,1, "i love you!");
        cout << "Server loaded!\n";
    }
};

string convert_month(int n){
    if (n < 9)
        return ('0' + to_string(n+1));
    else
        return to_string(n+1);

}

string convert_time(tm* t){
    string current_time = "";
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
    new_message.get_message(1,0);
    print_message(new_message);

}