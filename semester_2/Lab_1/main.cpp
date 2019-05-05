#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cctype>


std::string convert_month(int n);

std::string convert_time(tm* t);

class message{
private:
    std::string text = "";
    std::string cur_time;
    int author_id = -2;
    int adress_id = -2;
    char message_type = 'M';
    double mark = 0.0;
    /*
     * M --- Regular message
     * N --- News
     * Q --- Question
     * A --- Answer
     * I --- Invitation
     * */

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

    void set_type(char t){
        message_type = t;
    }
    char get_type(){
        return message_type;
    }

    void set_message(int aut, int adr, char typ, double mrk, std::string txt, std::string _time = "-1"){
        text = txt;
        if(_time == "-1")
            set_time();
        else
            cur_time = _time;
        message_type = typ;
        author_id = aut;
        adress_id = adr;
        mark = mrk;
    }
    double get_mark(){
        return mark;
    }

    void print(const std::string &author_name, const std::string &adress_name, bool mrk = false){
        if(mrk)
            std::cout <<"[" << mark << "]" << "\n";
        std::cout <<"(" << message_type << ") " << author_name << " -> " << adress_name << ": " << text << " :: " << cur_time << "\n";
    }

    std::string to_string(std::string login_auth, std::string login_adr){
        std::string res = "";
        res += login_auth + "\n";
        res += login_adr + "\n";
        res += message_type;
        res += "\n";
        int mrk = mark*1000;
        res += std::to_string(mrk);
        res += "\n";
        res += text + "\n";
        res += cur_time + "\n";
        return res;
    }
};

bool starts(message m, std::string s){
    std::string t = m.get_text();
    if(t.length() < s.length()) 
        return false;
    for(int i = 0, l = s.length(); i  < l; i++)
        if(s[i] != t[i])
            return false;
    
    return true;
}

bool fits_time(std::string t0, std::string t1){
    int time[2][6];
    std::string tmp = "";
    int cnt = 0;
    for(int j = 0; j < 6; j++){
        tmp = "";
        while(!(t0[cnt] == '.' || t0[cnt] == ':'|| t0[cnt] == ' ' || cnt == t0.size()))
            tmp+=t0[cnt++];
        cnt++;
        time[0][6-j-1] = stoi(tmp);
    }
    cnt = 0;
    for(int j = 0; j < 6; j++){
        tmp = "";
        while(!(t1[cnt] == '.' || t1[cnt] == ':'|| t1[cnt] == ' ') || cnt == t1.size())
            tmp+=t1[cnt++];
        cnt++;
        time[1][6-j-1] = std::stoi(tmp);
    }
    std::swap(time[0][3],time[0][5]);
    std::swap(time[1][3],time[1][5]);
    for (int i = 0; i < 6; i++){
        if(time[0][i] < time[1][i])
            return false;
        if(time[0][i] > time[1][i])
            return true;
    }
        return true;
}

double spam_mark(std::string s){
    double spam  = 0.0;
    int l = 2*(s.length()-2);
    for(int i = 2, k = s.length(); i < k; i++){
        if(s[i] == s[i-1]){
            spam += 1.0/l;
            //std::cout << spam << std::endl;
        }
        if(s[i] == s[i-2]){
            spam += 1.0/l;
            //std::cout << spam << std::endl;
        }
    }


    return spam;
}

class server{
private:
    int CNT_USERS = 2;

public:
    std::vector <message> messages;
    std::vector <std::string> name;
    std::map <std::string, int> id;
    std::set <std::string> names;
    std::set <char> types = {'M','N','Q','A', 'I'};

    void clear_all(){
        names.clear();
        id.clear();
        name.clear();
        messages.clear();
        CNT_USERS = 2;
        names.insert("Admin");
        id["TOALL"] = 0;
        id["Admin"] = 1;
        name.push_back("TOALL");
        name.push_back("Admin");
    }

    void load() {
        int CNT_MES;
        message m;
        clear_all();
        std::string auth, adr, txt, time;
        double mark;
        char typ;
        bool binary = 1;
        if(binary){
            std::ifstream bin("binary_backup.txt", std::ios::binary);
            bin.read((char*)&CNT_MES, sizeof(int));

            messages.resize(CNT_MES);
            int name_size;
            char temp_string[100];
            std::cout << CNT_MES << std::endl;
            for(int i = 0; i <CNT_MES; i++){
                bin.read((char*)&name_size, sizeof(int));
                bin.read(reinterpret_cast<char *>(&temp_string),name_size);
                temp_string[name_size] = '\0';
                auth = temp_string;

                bin.read((char*)&name_size, sizeof(int));
                bin.read(reinterpret_cast<char *>(&temp_string),name_size);
                temp_string[name_size] = '\0';
                adr = temp_string;

                bin.read(reinterpret_cast<char *>(&temp_string),1);
                typ = temp_string[0];

                bin.read((char*)&name_size, sizeof(int));
                mark = name_size/1000.0;

                bin.read((char*)&name_size, sizeof(int));
                bin.read(reinterpret_cast<char *>(&temp_string),name_size);
                temp_string[name_size] = '\0';
                txt = temp_string;


                bin.read((char*)&name_size, sizeof(int));
                bin.read(reinterpret_cast<char *>(&temp_string),name_size);
                temp_string[name_size] = '\0';
                time = temp_string;

                if(names.count(auth) == 0){
                    names.insert(auth);
                    id[auth] = CNT_USERS++;
                    name.push_back(auth);
                    m.set_author(id[auth]);
                }
                if(names.count(adr) == 0){
                    names.insert(adr);
                    id[adr] = CNT_USERS++;
                    name.push_back(adr);
                    m.set_adress(id[adr]);
                }

                m.set_message(id[auth],id[adr],typ,spam_mark(txt),txt,time);
                messages[i] = m;
            }
            bin.close();
            std ::cout << "Server loaded from binary!\n";
        }
        else{
            std::ifstream in("backup.txt");
            in >> CNT_MES;
            messages.resize(CNT_MES);
            getline(in,auth,'\n');
            int marking;
            for(int i = 0; i <CNT_MES; i++){
                getline(in, auth, '\n');
                getline(in, adr, '\n');
                getline(in,txt,'\n');
                typ = txt[0];
                in >> marking;
                mark = marking/1000.0;
                getline(in,txt,'\n');
                getline(in, txt, '\n');
                getline(in, time, '\n');
                if(names.count(auth) == 0){
                    names.insert(auth);
                    id[auth] = CNT_USERS++;
                    name.push_back(auth);
                }
                if(names.count(adr) == 0){
                    names.insert(adr);
                    id[adr] = CNT_USERS++;
                    name.push_back(adr);
                }
                m.set_message(id[auth],id[adr],typ,mark,txt,time);
                messages[i] = m;

            }
            in.close();

        }

    }

    void save() {
        std::ofstream out("backup.txt");
        out << messages.size() << std::endl;
        for(auto m : messages)
            out << m.to_string(name[m.get_author()],name[m.get_adress()]);
        out.close();
        std ::cout << "All saved!\n";

        std::string sname;
        std::ofstream bout("binary_backup.txt", std::ios::binary);
        int cnt_mes = messages.size();
        int name_size; int marking;
        char typ[1];
        bout.write((char*)&cnt_mes, sizeof(int));
        for(auto m : messages){
            name_size = name[m.get_author()].size();
            bout.write((char*)&name_size, sizeof(int));
            bout.write(name[m.get_author()].c_str(),name_size);

            name_size = name[m.get_adress()].size();
            bout.write((char*)&name_size, sizeof(int));
            bout.write(name[m.get_adress()].c_str(),name_size);

            typ[0] = m.get_type();
            bout.write((char*)typ,1);

            marking = m.get_mark()*1000;
            bout.write((char*)&marking, sizeof(int));

            name_size = m.get_text().size();
            bout.write((char*)&name_size, sizeof(int));
            bout.write(m.get_text().c_str(),name_size);

            name_size = m.get_time().size();
            bout.write((char*)&name_size, sizeof(int));
            bout.write(m.get_time().c_str(),name_size);


        }

        bout.close();
        std ::cout << "All binary-saved!)\n";
    }

    void print(int from = 0, int to = 0){
        std::cout << "Messages";
        std::cout << (from != 0 ? " from " + name[from] : "");
        std::cout << (to != 0 ? " to " + name[to] : "");
        std::cout << ":\n";
        if(from == 0 && to == 0){
            for(auto m : messages){
                m.print(name[m.get_author()],name[m.get_adress()]);
            }
        }
        else{
            for(auto m : messages){
                if((from == m.get_author() || from == 0) && (to == m.get_adress() || to == 0))
                    m.print(name[m.get_author()],name[m.get_adress()]);
            }
        }
        std::cout << "---------------------------\n";
    }

    void print(std::string from, std::string to = "TOALL"){
        print(id[from],id[to]);
    }
    
    void find_by_start(std::string start){
        std::cout << "Messages startin with \"" << start << "\":\n";
        for(auto m:messages){
            if(starts(m,start)){
                m.print(name[m.get_author()],name[m.get_adress()]);
            }
        }
        std::cout << "---------------------------\n";
    }

    void find_by_type_mark(char typ, double mark){
        std::cout << "Messages of type \'" << typ << "\', with mark not less than " << mark << ":\n";
        for(auto m: messages){
            if(m.get_type() == typ && m.get_mark() >= mark){
                m.print(name[m.get_author()],name[m.get_adress()],true);
            }
        }
        std::cout << "---------------------------\n";
    }

    void find_by_author_time(std::string athr, std::string time_st, std::string time_end){
        std::cout << "All messages from " << athr;
        std::cout << " that were send between " << time_st;
        std::cout << " and " << time_end << " :\n";
        for(auto m:messages){
            if(athr == name[m.get_author()] && fits_time(m.get_time(),time_st) && fits_time(time_end,m.get_time()))
                m.print(name[m.get_author()],name[m.get_adress()]);
        }
        std::cout << "---------------------------\n";
    }

    void add_message(message m){
        messages.push_back(m);
    }

    void new_message(){
        std::string author, adress, type, Text;
        getline(std::cin, author); // skip
        std::cout << "Enter your name:\n";
        getline(std::cin, author);
        std::cout << "Whom is your message for:\n";
        getline(std::cin, adress);
        std::cout << "What type is your message (for others better to understand)";
        std::cout << "You can choose between:\n";
        std::cout << "\"M\" - regular message\n";
        std::cout << "\"N\" - news\n";
        std::cout << "\"Q\" - question\n";
        std::cout << "\"A\" - answer\n";
        std::cout << "\"I\" - invitation\n";
        std::cout << "Your choise (please, uppercase): ";
        getline(std::cin, type);
        std::cout << "Enter your message:\n";
        getline(std::cin, Text);
        message m;
        if(names.count(author) == 0){
            id[author] = CNT_USERS++;
            names.insert(author);
            name.push_back(author);

        }
        if(names.count(adress) == 0){
            id[adress] = CNT_USERS++;
            names.insert(adress);
            name.push_back(adress);
        }
        m.set_message(id[author],id[adress],(types.count(type[0]) == 0 ? 'M' : type[0]),spam_mark(Text), Text);
        add_message(m);
    }

    void find_messages(){
        char key, typ;
        double mrk;
        std::string a,t,t1;
        std::cout << "Please, choose searching type:\n";
        std::cout << "A - search by starting symbols\n";
        std::cout << "B - search by type and spam system marking\n";
        std::cout << "C - search by author and time period\n";
        std::cout << "D - search by author and/or receiver\n";
        std::cout << "Your choise (please, uppercase): ";
        std::cin >> key;
        switch(key){
            case 'A':
                std::cout << "Starting symbols:";
                getline(std::cin,t);//skip \n
                getline(std::cin,t);
                find_by_start(t);
                break;
            case 'B':
                std::cout << "Enter type:";
                std::cin >> typ;
                std::cout << "Enter mark:";
                std::cin >> mrk;
                find_by_type_mark(typ,mrk);
                break;
            case 'C':
                std::cout << "Enter author:";
                getline(std::cin,a); // skip \n
                getline(std::cin,a);
                std::cout << "Enter start time (format reqiured : HOURS:MINUTES:SECONDS DAY.MONTH.YEAR):";
                getline(std::cin,t);
                std::cout << "Enter end time (format reqiured : HOURS:MINUTES:SECONDS DAY.MONTH.YEAR):";
                getline(std::cin,t1);
                find_by_author_time(a,t,t1);
                break;
            case 'D':
                std::cout << "Enter author:";
                getline(std::cin,a); // skip \n
                getline(std::cin,a);
                std::cout << "Enter adressant (possibly left empty):";
                getline(std::cin,t);
                if(t == "\n" || t == "")
                    print(a);
                else
                    print(a,t);
                break;
            default:
                std::cout << "No such command.\n";
                break;

        }
    }
};

std::string convert_month(int n){
    return n < 9 ? '0' + std::to_string(n + 1) : std::to_string(n + 1);
}

std::string convert_time(tm* t){
    return std::to_string((*t).tm_hour+3) +':'+ std::to_string((*t).tm_min) +':'+ std::to_string((*t).tm_sec) + " " + std::to_string((*t).tm_mday) +'.'+ convert_month((*t).tm_mon) +'.'+ std::to_string((*t).tm_year+1900);
}


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
        std::cout << "Enter \"p\" to print all messages\n";
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
            case 's':
                S.save();
                break;
            case 'l':
                S.load();
                break;
            case 'p':
                S.print();
                break;
            case 'f':
                S.find_messages();
                break;
            case 'q':
                S.load();
                return;
            default:
                std::cout << "No such command.\n";
                break;
        }
    }
}


void demo() {
    server S;
    S = *(new server());
    double t = spam_mark("aaaaaaab");
    S.load();
    S.print();
    S.print("Tester","Admin");
    S.print("Admin");

    S.find_by_start("I");
    S.find_by_author_time("Freddy","00:00:00 27.04.2019","11:10:10 28.04.2019");
    S.find_by_type_mark('M', 0.1);

    S.new_message();
    S.save();


}

void benchmark() {

    std::cout << "Rewriting \"benchmark.txt\"...\n";
    //  freopen("benchmark.txt","w",stdout);

}


int main() {
    int key;
    while(true) {
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
                return 0;
            case 3:
                benchmark();
                return 0;
            case 4:
                return 0;
            default:
                std::cout << "Try another command!\n";

        }
    }
}