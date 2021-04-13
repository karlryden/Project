#include "newsgroup.h"
#include <algorithm>
#include <iostream>
#include <stdexept>

using std::string;
using std::find;
using std::vector;

unsigned int NewsGroup::count = 0;

NewsGroup::NewsGroup(const string& n) : title{n}, id{count++} {}

Article NewsGroup::get_article(const unsigned int id) const {
    auto res=std::find_if(ng.begin(), ng.end(), [id](const Article& a) {return a.id == id;});
    if(res==ng.end()){
        throw NoSuchElement("element not found");            //ngt exception
    }else{
        return *res;
    }
    
}
bool NewsGroup::set_article(const Article& a){
    auto curr=std::find_if(ng.begin(), ng.end(), [title](const Article& a){return a.get_title()==title;});
    if(curr!=ng.end()){
        return false;
    } else{
        ng.push_back(a);
        return true;
    }
}
bool NewsGroup::remove_article(const std::string& title){
    auto curr=std::find_if(ng.begin(), ng.end(), [title](const Article& a){return a.get_title()==title;});
    if(curr==ng.end()){
        return false;
    }
    else{
        ng.erase(curr);
        return true;
    }
}
string NewsGroup::to_string() const {
    return id + " " + title + " ";;
}
bool operator==(const NewsGroup& n) const{
    return n.id==id;
}

Article make_article(const std::string& title, const std::string& author, const std::string& text){
    return Article(title, author, text);
}

vector::iterator NewsGroup::begin(){return ng.begin();}
vector::iterator NewsGroup::end(){return ng.end();}
vector::size_type NewsGroup::size(){return ng.size();}
std::string NewsGroup::get_title(){return title;}
