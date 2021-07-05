#include<iostream>
#include<fstream>
#include<direct.h>
#include<algorithm>
#include<string>
using namespace std;

class Sqlcmd{
    public:
        void Slect();
        void Update();
        void Delete();
        void Insert_Into();
        void Create_Database();
        void Alter_Database();
        void Create_Table();
        void Alter_Table();
        void Drop_Table();
        void Create_Index();
        void Drop_Index();
};

class input{
    string cmd;
    enum keyword{create,Delete,insert,select,show,update};
    public:
        void get(){
            cin>>cmd;
            for_each(cmd.begin(), cmd.end(), [](char & c){ c = ::tolower(c); });
        }
        input(){
            bool check = true;
            while(check){
                get();
                if(cmd == "exit"){
                    check = false;
                    continue;
                }
                if(cmd == "create"){
                    get();
                    if(cmd == "database"){
                        cin>>cmd;
                        cmd = "data/"+cmd;
                        mkdir(cmd.c_str());
                    }
                    else if(cmd == "table"){
                        cin>>cmd;
                        ofstream file("data/"+cmd+".txt");
                        file<<cmd;
                        file.close();
                    }
                }
                else if(cmd == "delete"){
                    get();
                    if(cmd == "table"){
                        cin>>cmd;
                        cmd = "data/"+cmd+".txt";
                        remove(cmd.c_str());
                    }
                }
                else if(cmd == "insert");
                else if(cmd == "select");
                else if(cmd == "show");
                else if(cmd == "update");
                
            }
        }
};