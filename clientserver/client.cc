

//#include "client.h"
#include "protocol.h"
#include "connectionclosedexception.h"
#include "connection.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::stoi;
using std::cerr;
using std::getline;

const string MSG="\nPick an action (enter number 0-7, 0 to quit): \n1. List newsgroups. \n2. Create newsgroup. \n3. Delete newsgroup. \n4. List articles in newsgroup. \n5. Create article. \n6. Delete article. \n7. Get article.\n";

string read_string(){
    string temp;
    string res;
    cin>>res;
    getline(cin,temp);
    res+=temp;
    return res;
}
void write_string(string string_p, Connection& conn){
    //        conn.write(static_cast<unsigned char>(Protocol::PAR_STRING));
            for(unsigned char c: string_p){
                cout<<c;
    //            conn.write(c);
            }
            cout<<endl;
}

int read_nbr(){
    string input{};
    int res{};
    while(cin>>input){
        try{
            res=stoi(input);
//            cout<<res<<endl;
            return res;
        }catch(std::exception& e){
            cout<<"Not a valid entry. Enter a number."<<endl;        //skulle kunna ha en kontroll för range också - kräver exvis attribut för att hålla kolla på vilka id som finns
        }
    }
    cout<<"Should not be reached"<<endl;
    return -1;
}

void create_article(Connection& conn){
    int ng{};
    string title{};
    string author{};
    string text{};
    cout<<"Enter identification number of the relevant newsgroup."<<endl;
    ng=read_nbr();
    cout<<"Enter title of the new article."<<endl;
    title=read_string();
    cout<<"Enter author of the new article"<<endl;
    author=read_string();
    cout<<"Enter text."<<endl;
    text=read_string();
    
//    conn.write(static_cast<unsigned char>(Protocol::COM_CREATE_ART));
//    conn.write(static_cast<unsigned char>(Protocol::PAR_NUM));
//    conn.write(static_cast<unsigned char>(ng));
    write_string(title, conn);
    write_string(author, conn);
    write_string(text, conn);
}

void get_or_delete_article(){
    int ng{};
    int art{};
    cout<<"Enter identification number of the relevant newsgroup."<<endl;
    ng=read_nbr();
    cout<<"Enter identification number of the relevant article."<<endl;
    art=read_nbr();
//    conn.write(static_cast<unsigned char>(Protocol::COM_DELETE_ART));
    //    conn.write(static_cast<unsigned char>(Protocol::PAR_NUM));
    //    conn.write(static_cast<unsigned char>(ng));
    //    conn.write(static_cast<unsigned char>(Protocol::PAR_NUM));
    //    conn.write(static_cast<unsigned char>(art));
}



void process_input(Connection& conn, int& input){
    if(!(cin>>input)){
        std::cerr<<"Error incorrect input. Exiting..."<<endl;
        exit(1);
    }
    if(input==0){
        return;
    }
    string string_p{};
    int num_p{-1};
    switch (input) {
        case 1:
            cout<<"Listing newsgroups..."<<endl;
//            conn.write(static_cast<unsigned char>(Protocol::COM_LIST_NG));
            
            break;
        case 2:
            cout<<"Enter title of the new newsgroup."<<endl;
            string_p=read_string();
//            conn.write(static_cast<unsigned char>(Protocol::COM_CREATE_NG));
            break;
        case 3:
            cout<<"Enter identification number of the newsgroup to be deleted."<<endl;
            num_p=read_nbr();
//            conn.write(static_cast<unsigned char>(Protocol::COM_DELETE_NG));
           
            break;
        case 4:
            cout<<"Enter identification number of the newsgroup to be listed."<<endl;
            num_p=read_nbr();
//            conn.write(static_cast<unsigned char>(Protocol::COM_LIST_ART));
            break;
        case 5:
            create_article(conn);
            break;
        case 6:
            get_or_delete_article();
            break;
        case 7:
            get_or_delete_article();
            break;
        default:
            cout<<"please enter a number between 0 and 7."<<endl;
            return;
    }
    
    if(string_p!=""){
        write_string(string_p, conn);
    }
    
    if(num_p!=-1){
//        conn.write(static_cast<unsigned char>(Protocol::PAR_NUM))
        cout<<num_p<<endl;
//        conn.write(num_p);
    }
//    conn.write(static_cast<unsigned char>(Protocol::COM_END));
    
}

void list(Connection& conn){
    string res{};
    Protocol ack_or_nak=static_cast<Protocol>(conn.read());                //om 1 -> PAR_NUM, om 4->ANS_ACK elr ANS_NACK
    if(ack_or_nak==Protocol::ANS_NAK){
        conn.read();                                                       //nak
        cout<<"Error, newsgroup does not exist"<<endl;
        conn.read();                                                        //err does not exist
        conn.read();                                                        //ans_end
        return;
    } else if(ack_or_nak == Protocol::ANS_ACK){
        conn.read();                                                        //ack
    }
    int n=conn.read();
    for(int i=0; i<n; ++i){
        conn.read();                                                        //par num
        int id=conn.read();
        conn.read();                                                        //par string
        string title{};
        Protocol tag = static_cast<Protocol>(conn.read());
        while(tag != Protocol::PAR_NUM && tag != Protocol::ANS_END){
            title+=conn.read();
        }
        res+=id + " " + title + "\n";
    }
    cout<<res<<endl;
}

void create(Connection& conn){
    string res{};
    Protocol tag = static_cast<Protocol>(conn.read());
    if(tag == Protocol::ANS_ACK){
        res = "Creation successful"; //HÄR GÅR DET ATT VARA MER SPEICIFIK
    } else {
        Protocol tag2 = static_cast<Protocol>(conn.read());
        if(tag2 == Protocol::ERR_NG_ALREADY_EXISTS){
            res = "Error: Newsgroup already exists";
        } else {
            res = "Error: Newsgroup does not exist";
        }
    }
    conn.read();                                                             //ans_end
    cout<<res<<endl;
}

void remove(Connection& conn){
    string res{};
    Protocol tag = static_cast<Protocol>(conn.read());
    if(tag == Protocol::ANS_ACK){
        res = "Deletion successful"; //HÄR GÅR DET ATT VARA MER SPEICIFIK
    } else{
        Protocol tag2 = static_cast<Protocol>(conn.read());
        if(tag2 == Protocol::ERR_NG_DOES_NOT_EXIST){
            res = "Error: Newsgroup does not exist";
        } else {
            res = "Error: Article does not exist";
        }
    }
    conn.read();                                                             //ans_end
    cout<<res<<endl;
}

void get_art(Connection& conn){
    Protocol tag = static_cast<Protocol>(conn.read());
    if(tag == Protocol::ANS_NAK){
        Protocol tag2 = static_cast<Protocol>(conn.read());
        if(tag2 == Protocol::ERR_NG_DOES_NOT_EXIST){
            cout << "Error: Newsgroup does not exist"<<endl;;
        } else {
            cout << "Error: Article does not exist"<<endl;;
        }
    } else {
        string str;
        for(int i = 0; i < 3; ++i){
            Protocol tag = static_cast<Protocol>(conn.read());
            while(tag !=Protocol::PAR_STRING && tag !=Protocol::ANS_END){
                str+=conn.read();
            }
            cout << str << endl;
            str = "";
        }
    }
}

void process_response(Connection& conn){
    Protocol ans_tag = static_cast<Protocol>(conn.read());
    
       switch (ans_tag) {
        case Protocol::ANS_LIST_NG:
            list(conn);
               
            break;
        case Protocol::ANS_CREATE_NG:
            create(conn);
        
            break;
        case Protocol::ANS_DELETE_NG:
            remove(conn);
            
            break;
        case Protocol::ANS_LIST_ART:
            list(conn);
            break;
        case Protocol::ANS_CREATE_ART:
            create(conn);
            
            break;
        case Protocol::ANS_DELETE_ART:
               remove(conn);
            
            break;
        case Protocol::ANS_GET_ART:
               get_art(conn);
            
            break;
        default:
            cout<<"Invalid server response"<<endl;
            return;
    }
    conn.read();                                                        //ans_end
}


int main(/*int argc, char* argv[]*/){

    Connection conn{"host",1};
//    cout<<"\n"<<conn.isConnected() << " hej" <<endl;
    cout<<MSG<<endl;
    int input{};
    while(true){
        process_input(conn, input);
        if(input==0){
            cout<<"Exiting..."<<endl;
            break;
        }
        process_response(conn);
        cout<<MSG<<endl;
    }
    
}
