#include "client.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::stoi;
using std::cerr;
using std::getline;


string read_string(){
    string temp;
    string res;
    cin>>res;
    getline(cin,temp);
    res+=temp;
    return res;
}
void write_string(string string_p, const Connection& conn){
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

void create_article(const Connection& conn){
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
    
    conn.write(static_cast<unsigned char>(Protocol::COM_CREATE_ART));
    conn.write(static_cast<unsigned char>(Protocol::PAR_NUM));
    writeNumber(conn, ng);
    conn.write(static_cast<char>(Protocol::PAR_STRING));
    writeString(conn, title);
    conn.write(static_cast<char>(Protocol::PAR_STRING));
    writeString(conn, author);
    conn.write(static_cast<char>(Protocol::PAR_STRING));
    writeString(conn, text);
}

void delete_article(const Connection& conn){
    int ng{};
    int art{};
    cout<<"Enter identification number of the relevant newsgroup."<<endl;
    ng=read_nbr();
    cout<<"Enter identification number of the relevant article."<<endl;
    art=read_nbr();
    conn.write(static_cast<unsigned char>(Protocol::COM_DELETE_ART));
    conn.write(static_cast<unsigned char>(Protocol::PAR_NUM));
    writeNumber(conn, ng);
    conn.write(static_cast<unsigned char>(Protocol::PAR_NUM));
    writeNumber(conn, art);
}

void get_article(const Connection& conn){
    int ng{};
    int art{};
    cout<<"Enter identification number of the relevant newsgroup."<<endl;
    ng=read_nbr();
    cout<<"Enter identification number of the relevant article."<<endl;
    art=read_nbr();
    conn.write(static_cast<unsigned char>(Protocol::COM_GET_ART));
    conn.write(static_cast<unsigned char>(Protocol::PAR_NUM));
    writeNumber(conn, ng);
    conn.write(static_cast<unsigned char>(Protocol::PAR_NUM));
    writeNumber(conn, art);
}



void process_input(const Connection& conn, int& input){
    
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
            conn.write(static_cast<unsigned char>(Protocol::COM_LIST_NG));
            
            break;
        case 2:
            cout<<"Enter title of the new newsgroup."<<endl;
            string_p=read_string();
            conn.write(static_cast<unsigned char>(Protocol::COM_CREATE_NG));
            break;
        case 3:
            cout<<"Enter identification number of the newsgroup to be deleted."<<endl;
            num_p=read_nbr();
            conn.write(static_cast<unsigned char>(Protocol::COM_DELETE_NG));
           
            break;
        case 4:
            cout<<"Enter identification number of the newsgroup to be listed."<<endl;
            num_p=read_nbr();
            conn.write(static_cast<unsigned char>(Protocol::COM_LIST_ART));
            break;
        case 5:
            create_article(conn);
            break;
        case 6:
            delete_article(conn);
            break;
        case 7:
            get_article(conn);
            break;
        default:
            cout<<"please enter a number between 0 and 7."<<endl;
            return;
    }
    if(num_p!=-1){
        conn.write(static_cast<unsigned char>(Protocol::PAR_NUM));
        writeNumber(conn, num_p);
        
        
    }
    if(string_p!=""){
        conn.write(static_cast<unsigned char>(Protocol::PAR_STRING));
        writeString(conn, string_p);
    }
    
    
    conn.write(static_cast<unsigned char>(Protocol::COM_END));
    
    
}

void list(const Connection& conn){
    string res{};
    char ack_or_nak=conn.read();                //om 1 -> PAR_NUM, om 4->ANS_ACK elr ANS_NACK
    
    
    if(ack_or_nak== static_cast<char>(Protocol::ANS_NAK)){
                                                            //nak
        cout<<"Error, newsgroup does not exist"<<endl;
        conn.read();                                                        //err does not exist
        conn.read();                                                        //ans_end
        return;
    } else if(ack_or_nak== static_cast<char>(Protocol::ANS_ACK)){
                                                             //ack
        conn.read();                                                        //par num
        int n{readNumber(conn)};
        
        for(int i=0; i<n; i++){
            
            conn.read();                                                        //par num
            int id{readNumber(conn)};
            conn.read();                                                        //par string
            string title{readString(conn)};
            
            res+=std::to_string(id) + " " + title + "\n";
        }
        conn.read();                                                        // ans_end
        cout<<res<<endl;
    }
}


void list_newsgroup(const Connection& conn){
    string res{};
    conn.read();                                                        //par num
    int n{readNumber(conn)};
    for(int i=0; i<n; ++i){
        conn.read();                                                        //par num
        int id{readNumber(conn)};
        
        conn.read();                                                        //par string
        string title{readString(conn)};
        
        res+=std::to_string(id) + " " + title + "\n";
    }
    conn.read();                                                        // ans_end
    cout<<res<<endl;
}

void create(const Connection& conn){
    string res{};
    char tag = static_cast<char>(conn.read());
    if(tag == static_cast<char>(Protocol::ANS_ACK)){
        res = "Creation successful"; //HÄR GÅR DET ATT VARA MER SPEICIFIK
    } else {
        char tag2 = static_cast<char>(conn.read());
        if(tag2 == static_cast<char>(Protocol::ERR_NG_ALREADY_EXISTS)){
            res = "Error: Newsgroup already exists";
        } else {
            res = "Error: Newsgroup does not exist";
        }
    }
    conn.read();                                                             //ans_end
    cout<<res<<endl;
}

void remove(const Connection& conn){
    string res{};
    char tag = static_cast<char>(conn.read());
    if(tag == static_cast<char>(Protocol::ANS_ACK)){
        res = "Creation successful"; //HÄR GÅR DET ATT VARA MER SPEICIFIK
    } else {
        char tag2 = static_cast<char>(conn.read());
        if(tag2 == static_cast<char>(Protocol::ERR_NG_ALREADY_EXISTS)){
            res = "Error: Newsgroup already exists";
        } else {
            res = "Error: Newsgroup does not exist";
        }
    }
    conn.read();                                                             //ans_end
    cout<<res<<endl;
}

void get_art(const Connection& conn){
    char tag = static_cast<char>(conn.read());
    if(tag == static_cast<char>(Protocol::ANS_NAK)){
        char tag2 = static_cast<char>(conn.read());
        if(tag2 == static_cast<char>(Protocol::ERR_NG_DOES_NOT_EXIST)){
            cout << "Error: Newsgroup does not exist"<<endl;;
        } else {
            cout << "Error: Article does not exist"<<endl;;
        }
    } else {
        string str;
        for(int i = 0; i < 3; i++){
            char tag = static_cast<char>(conn.read());
            str += readString(conn);
            cout << str << endl;
            str = "";
        }
        conn.read(); //ans_end
    }
}

void process_response(const Connection& conn){
    Protocol ans_tag = static_cast<Protocol>(conn.read());
    
       switch (ans_tag) {
        case Protocol::ANS_LIST_NG:
            list_newsgroup(conn);
               
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
    
    
    cout << "exiting process response" << endl;
}


// int main(/*int argc, char* argv[]*/){

//     Connection conn{"host",1};
// //    cout<<"\n"<<conn.isConnected() << " hej" <<endl;
//     cout<<MSG<<endl;
//     int input{};
//     while(true){
//         process_input(input);
//         if(input==0){
//             cout<<"Exiting..."<<endl;
//             break;
//         }
//         process_response(conn);
//         cout<<MSG<<endl;
//     }
    
// }
