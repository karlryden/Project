#include "newsserver.h"
#include "newsgroup.h"
#include "memorydb.h"
#include "diskdb.h"
#include <iostream>
#include <algorithm>
#include "messagehandler.h"
NewsServer::NewsServer(int port): Server(port), db{new MemoryDatabase()}{}


std::string NewsServer::get_newsgroup(unsigned int id){
    return db->get_newsgroup(id);
}

std::string NewsServer::get_article(unsigned int ng_id, unsigned int art_id){
    return db->get_article(ng_id, art_id);/*db->get_article(title, author, text);*/
}



bool NewsServer::create_newsgroup(std::string title){
    return db->set_newsgroup(title);
}
bool NewsServer::create_article(unsigned int id, std::string title, std::string author, std::string text){
    return db->set_article(id, title, author, text);
}

bool NewsServer::remove_newsgroup(unsigned int id){
    return db->remove_newsgroup(id);
}
bool NewsServer::remove_article(unsigned int ng_id, unsigned int art_id){
    return db->remove_article(ng_id, art_id);
}

std::string NewsServer::list_newsgroups(){
    return db->list_newsgroups();
    // \n?
}
std::string NewsServer::list_articles(unsigned int id){
    return db->list_articles(id);
    
}
    


std::string NewsServer::handle_request(const std::shared_ptr<Connection>& conn){
    std::string out;
    int comm{conn->read()};
    switch (comm){
        case(static_cast<int>(Protocol::COM_LIST_NG)):
        {
            // Read the end-byte
            conn->read();

            conn->write(static_cast<int>(Protocol::ANS_LIST_NG));
            std::string test{list_newsgroups()};
            std::cout << test << std::endl;
            std::istringstream ss {test};
            int n;
            
            // Read number of newsgroups, write to conn. write id and name to conn. 
            ss >> n;
            conn->write(static_cast<char>(Protocol::PAR_NUM));
            writeNumber(conn, n);
            int length{};
            while (ss >> n){
                std::string s;
                ss >> length;
                char ch;
                std::cout << length << std::endl;
                
                for (int i = 0; i < length + 1; i++){
                    ch = ss.get();
                    std::cout << ch << std::endl;
                    if (i > 0) {
                        s += ch;
                    }
                } 
                std::cout << s << std::endl;
                std::cout << "----" << std::endl;
                conn->write(static_cast<char>(Protocol::PAR_NUM));
                writeNumber(conn, n);
                std::cout << n << std::endl;
                conn->write(static_cast<char>(Protocol::PAR_STRING));
                std::cout << s.size() << std::endl;
                writeString(conn, s);
            }
            conn->write(static_cast<int>(Protocol::ANS_END));
            
            break;
        }
        case(static_cast<int>(Protocol::COM_CREATE_NG)):{
            // Read the par-string byte, read the string, read the end-byte
            conn->read();
            std::string title{readString(conn)};
            conn->read();
            std::cout << title << std::endl;
            // Write the reply
            
            conn->write(static_cast<int>(Protocol::ANS_CREATE_NG));
            if (create_newsgroup(title)){
                conn->write(static_cast<char>(Protocol::ANS_ACK));
            }
            else{
                conn->write(static_cast<char>(Protocol::ANS_NAK));
                conn->write(static_cast<char>(Protocol::ERR_NG_ALREADY_EXISTS));
            }
            conn->write(static_cast<int>(Protocol::ANS_END));
            break;
        }
        case (static_cast<int>(Protocol::COM_DELETE_NG)):{
            // Read the par-N byte and the ID
            conn->read();
            int id{readNumber(conn)};
            conn->read();
            conn->write(static_cast<int>(Protocol::ANS_DELETE_NG));
            if (remove_newsgroup(id)){
                conn->write(static_cast<char>(Protocol::ANS_ACK));
            }
            else {
                conn->write(static_cast<char>(Protocol::ANS_NAK));
                conn->write(static_cast<char>(Protocol::ERR_NG_DOES_NOT_EXIST));
            }
            conn->write(static_cast<int>(Protocol::ANS_END));
            break;
        }
            
        case(static_cast<int>(Protocol::COM_LIST_ART)):{

            // Read the par-n byte, the ID, and the end-byte
            conn->read();
            int id{readNumber(conn)};
            conn->read();

            conn->write(static_cast<int>(Protocol::ANS_LIST_ART));
            std::string list {list_articles(id)};
            std::cout << list << std::endl;
            if (list.empty()){
                conn->write(static_cast<char>(Protocol::ANS_NAK));
                conn->write(static_cast<char>(Protocol::ERR_NG_DOES_NOT_EXIST));
            }
            else{
                conn->write(static_cast<char>(Protocol::ANS_ACK));
                std::istringstream ss{list};
                
                int N;
                int id;
                ss >> N;
                
                conn->write(static_cast<char>(Protocol::PAR_NUM));
                writeNumber(conn, N);
                for (int i = 0; i < N; i++){
                    int length{};
                    std::string s;
                    
                    ss >> id;
                    ss >> length;
                    for (int i = 0; i < length + 1; i ++){
                        char ch = ss.get();
                        if (i > 0) {
                            s += ch;
                        }
                    }
                    conn->write(static_cast<char>(Protocol::PAR_NUM));
                    writeNumber(conn, id);
                    
                    conn->write(static_cast<char>(Protocol::PAR_STRING));
                    writeString(conn, s);
                }
            }
            conn->write(static_cast<int>(Protocol::ANS_END));
            break;
        }
        case(static_cast<int>(Protocol::COM_CREATE_ART)):{
            int id;
            std::string title;
            std::string author;
            std::string text;
            // Read the NG-id
            conn->read();
            id = readNumber(conn);

            // read the title
            conn->read();
            title = readString(conn);

            // read the author
            conn->read();
            author = readString(conn);

            // Read the text
            conn->read();
            text = readString(conn);

            // Read the end-byte
            conn->read();
            
            conn->write(static_cast<int>(Protocol::ANS_CREATE_ART));
            
            if (create_article(id, title, author, text)){
                conn->write(static_cast<char>(Protocol::ANS_ACK));
            }
            else{
                conn->write(static_cast<char>(Protocol::ANS_NAK));
                conn->write(static_cast<char>(Protocol::ERR_NG_DOES_NOT_EXIST));
            }
            conn->write(static_cast<char>(Protocol::ANS_END));
            break;
        }
        case(static_cast<int>(Protocol::COM_DELETE_ART)):{
            int ng_id;
            int art_id;
            // read the ng id
            conn->read();
            ng_id = readNumber(conn);

            // read the art id
            conn->read();
            art_id = readNumber(conn);

            //read the end-byte
            conn->read();

            conn->write(static_cast<int>(Protocol::ANS_DELETE_ART));
            
            if (remove_article(ng_id, art_id)){
                conn->write(static_cast<char>(Protocol::ANS_ACK));
            }
            else {
                conn->write(static_cast<char>(Protocol::ANS_NAK));
                if (get_newsgroup(ng_id).empty()){
                    conn->write(static_cast<char>(Protocol::ERR_NG_DOES_NOT_EXIST));
                }
                else {
                    conn->write(static_cast<char>(Protocol::ERR_ART_DOES_NOT_EXIST));
                }
            }
            conn->write(static_cast<char>(Protocol::ANS_END));
            break;
        }
        case(static_cast<int>(Protocol::COM_GET_ART)):{
            int ng_id;
            int art_id;
            // read the ng id
            conn->read();
            ng_id = readNumber(conn);

            // read the art id
            conn->read();
            art_id = readNumber(conn);

            //read the end-byte
            conn->read();

            conn->write(static_cast<int>(Protocol::ANS_GET_ART));
            std::string article{get_article(ng_id, art_id)};
            if (!(article.empty())){
                    conn->write(static_cast<char>(Protocol::ANS_ACK));
                    std::string::size_type curr{0};
                    std::string::size_type   prev{0};
                    for (int j = 0; j < 3; j++){
                        curr = article.find_first_of("|", curr);
                        std::cout << article.substr(prev, curr - prev) << std::endl;

                        conn->write(static_cast<char>(Protocol::PAR_STRING));
                        writeString(conn, article.substr(prev, curr - prev));
                        curr++;
                        prev = curr;
                    }
            }
            else {
                conn->write(static_cast<char>(Protocol::ANS_NAK));
                if (get_newsgroup(ng_id).empty()){
                    conn->write(static_cast<char>(Protocol::ERR_NG_DOES_NOT_EXIST));
                }
                else {
                    conn->write(static_cast<char>(Protocol::ERR_ART_DOES_NOT_EXIST));
                }
            }
            conn->write(static_cast<char>(Protocol::ANS_END));
            break;
        }
        default:
            std::cout << "Hur hamnade vi här????" << std::endl;
            break;
        
    }
    
    return out;
}
