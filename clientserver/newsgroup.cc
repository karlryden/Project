#include "newsgroup.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

using std::string;
using std::find;
using std::vector;

unsigned int NewsGroup::count{0};

NewsGroup::NewsGroup(const string& n) : name{n}, id(count++) {}

Article NewsGroup::get_article(unsigned int id) const {
    auto res=std::find_if(ng.begin(), ng.end(), [id](const Article& a) {return a.id == id;});
    if(res == ng.end()){
        throw std::invalid_argument("element not found");           //ngt exception
    } else {
        return *res;
    }
}

bool NewsGroup::set_article(const Article& a){
    auto curr = std::find_if(ng.begin(), ng.end(), [a](const Article& art) {
        return (a.get_title() == art.get_title()) && (a.get_author() == art.get_author());
    });
    if(curr != ng.end()) {
        return false;
    } else{
        ng.push_back(a);
        
        return true;
    }
}
bool NewsGroup::remove_article(unsigned int id){
    auto curr = std::find_if(ng.begin(), ng.end(), [id](const Article& a){return a.id == id;});
    if(curr == ng.end()) {
        return false;
    } else {
        ng.erase(curr);
        return true;
    }
}

string NewsGroup::get_name() const {
    return name;
}

string NewsGroup::to_string() const {
    return name;
}

bool NewsGroup::operator==(const NewsGroup& n) const{
    return n.id == id;
}

