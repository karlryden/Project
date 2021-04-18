#include "memorydb.h"
#include <algorithm>
#include <iostream>
using std::string;
using std::vector;
using std::find;
using std::find_if;

string MemoryDatabase::get_newsgroup(unsigned int ng_id) const {
    NewsGroup ng{*find_if(table.begin(), table.end(), [ng_id](const NewsGroup& n) {return n.id == ng_id;})};
    
    return ng.to_string();
}

string MemoryDatabase::get_article(unsigned int ng_id, unsigned int a_id) const {
    
    NewsGroup ng{*find_if(table.begin(), table.end(), [ng_id](const NewsGroup& n) {return n.id == ng_id;})};
    
    Article a(ng.get_article(a_id));
    
    return a.to_string();
}

bool MemoryDatabase::set_newsgroup(string name) {                       //borde väl checka efter om den redan finns om newsgroups skulle vara unika och returnera false.
    NewsGroup ng{name};
    table.push_back(ng);    
    
    return true;
}

bool MemoryDatabase::set_article(unsigned int id, string tit, string aut, string tex) {
    // NewsGroup ng{*(table.find(ng_id))};
    Article a(tit, aut, tex);    
    return find_if(table.begin(), table.end(), [id](const NewsGroup& n) {return n.id == id;})->set_article(a);
}

bool MemoryDatabase::remove_newsgroup(unsigned int ng_id) {
    // return table.erase(ng_id);
    auto pos{find_if(table.begin(), table.end(), [ng_id](const NewsGroup& n) {return n.id == ng_id;})};
    if (pos != table.end()) {
        table.erase(pos);
        return true;
    }

    return false;
}

bool MemoryDatabase::remove_article(unsigned int ng_id, unsigned int a_id) {
   
    return find_if(table.begin(), table.end(), [ng_id](const NewsGroup& n) {return n.id == ng_id;})->remove_article(a_id);
}
vector<NewsGroup>::iterator MemoryDatabase::begin(){
    return table.begin();
}

vector<NewsGroup>::iterator MemoryDatabase::end(){
    return table.end();
}

int MemoryDatabase::size() {
    return static_cast<int>(table.size());
}

string MemoryDatabase::list_articles(unsigned int id){
    
    std::string res{};
    
    auto ng=std::find_if(table.begin(), table.end(), [id](const NewsGroup& n){return n.id==id;}); //get_newsgroup? men den returnerar string ?
    res+=std::to_string(ng->ng.size()) + " ";
    std::cout << ng->ng.size() << std::endl;
    std::for_each(ng->ng.begin(), ng->ng.end(), [&res](const Article& a){res+=std::to_string(a.id)+ " " + std::to_string(a.get_title().length()) + " " + a.get_title() + " ";});
    return res;
}

string MemoryDatabase::list_newsgroups(){
    string res{};
    res+=std::to_string(size()) + " ";
    std::for_each(begin(), end(), [&res](const NewsGroup& ng){res+=std::to_string(ng.id) + " " + std::to_string(ng.to_string().length()) + " " + ng.to_string() + " ";});
    return res;
}
