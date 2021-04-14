#include "newsserver.h"
#include "newsgroup.h"
#include "memorydb.h"
#include <iostream>
#include <algorithm>

NewsServer::NewsServer(int port): Server(port), db{new MemoryDatabase()}{}


std::string NewsServer::get_newsgroup(std::string title){
    return "";/*db->get_newsgroup(title);*/
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
    


std::string NewsServer::handle_request(int comm, std::vector<int>& arg_N, std::vector<std::string>& arg_s, int end){
    std::string out;
    switch (comm){
        case(static_cast<int>(Protocol::COM_LIST_NG)):
            out = list_newsgroups();
            break;
        case(static_cast<int>(Protocol::COM_CREATE_NG)):
            out = create_newsgroup(arg_s[0]);
            break;
        case (static_cast<int>(Protocol::COM_DELETE_NG)):
            out = remove_newsgroup(arg_N[0]);
            break;
        case(static_cast<int>(Protocol::COM_LIST_ART)):
            out = list_articles(arg_N[0]);
            break;
        case(static_cast<int>(Protocol::COM_CREATE_ART)):
            out = "article created";
            create_article(arg_N[0], arg_s[0], arg_s[1], arg_s[2]);
            break;
        case(static_cast<int>(Protocol::COM_DELETE_ART)):
            out = "article deleted";
            remove_article(arg_N[0], arg_N[1]);
            break;
        case(static_cast<int>(Protocol::COM_GET_ART)):
            out = get_article(arg_N[0], arg_N[1]);
            break;
        default:
            out = "CHECKCHECK";
            break;
        
    }
    
    return out;
}
