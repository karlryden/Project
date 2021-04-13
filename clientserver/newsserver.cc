#include "newsserver.h"
#include "newsgroup.h"
#include <algorithm>

NewsServer::NewsServer(): db{}, mh{}{}
NewsServer::NewsServer(Database& d) db{d}, mh{}{}

std::string NewsServer::get_newsgroup(std::string title){
    return db.get_newsgroup(title);
}

std::string NewsServer::get_article(std::string title, std::string author, std::string text){
    return db.get_article(title, author, text);
}



bool NewsServer::create_newsgroup(std::string title){
    return db.set_newsgroup(title);
}
bool NewsServer::create_article(std::string title, std::string author, std::string text, std::string boeufbourguignon){
    return db.set_article(title, author, text, boeufbourguignon);
}

bool NewsServer::remove_newsgroup(std::string title){
    return db.remove_newsgroup(title);
}
bool NewsServer::remove_article(std::string, std::string, std::string){
    return db.remove_article(title);
}

std::string NewsServer::list_newsgroups(){
    string res{};
    res+=db.size() + " ";
    std::for_each(db.begin(), db.end(), [&res](const NewsGroup& ng){res+=ng.to_string() + " "});        // \n?
}
std::string NewsServer::list_articles(std::string title){
    string res{};
    auto ng=std::find_if(db.begin(), db.end(), [title](const NewsGroup& n){return n.get_title()==title;}); //get_newsgroup? men den returnerar string ?
    res+=ng->size() + " ";
    std::for_each(ng->begin(), ng->end(), [&res](const Article& a){res+=a.id+ " " + a.get_title() + " "});
}
    


bool NewsServer::handle_request();
