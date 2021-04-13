#include "memorydb.h"
#include <algorithm>

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
    Article a{ng.get_article(a_id)};

    return a.to_string();
}

bool MemoryDatabase::set_newsgroup(string name) {
    NewsGroup ng{name};
    table.push_back(ng);    
    
    return true;
}

bool MemoryDatabase::set_article(string name, string tit, string aut, string tex) {
    // NewsGroup ng{*(table.find(ng_id))};
    NewsGroup ng{*find_if(table.begin(), table.end(), [name](const NewsGroup& n) {return n.get_name() == name;})};
    Article a(tit, aut, tex);

    return ng.set_article(a);
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
    NewsGroup ng{*find_if(table.begin(), table.end(), [ng_id](const NewsGroup& n) {return n.id == ng_id;})};
    
    return ng.remove_article(a_id);
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

