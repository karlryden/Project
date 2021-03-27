#include "memorydb.h"
#include <algorithm>

using std::string;
using std::find;
using std::find_if;

string MemoryDatabase::get_newsgroup(string name) const {
    NewsGroup ng{*find_if(table.begin(), table.end(), [name](const NewsGroup& n) {return n.name == name;})};
    
    return ng.to_string();
}

string MemoryDatabase::get_article(string name, string title, string author) const {
    NewsGroup ng{*find_if(table.begin(), table.end(), [name](const NewsGroup& n) {return n.name == name;})};
    Article a{ng.get_article(title, author)};

    return a.to_string();
}

bool MemoryDatabase::set_newsgroup(string name) {
    NewsGroup ng{name};
    // return (table.insert(ng)).second;
    table.push_back(ng);    
    
    return true;
}

bool MemoryDatabase::set_article(string name, string tit, string aut, string tex) {
    // NewsGroup ng{*(table.find(ng_id))};
    NewsGroup ng{*find_if(table.begin(), table.end(), [name](const NewsGroup& n) {return n.name == name;})};
    Article a(tit, aut, tex);

    return ng.set_article(a);
}

bool MemoryDatabase::remove_newsgroup(string name) {
    // return table.erase(ng_id);
    auto pos{find_if(table.begin(), table.end(), [name](const NewsGroup& n) {return n.name == name;})};
    if (pos != table.end()) {
        table.erase(pos);
        return true;
    }

    return false;
}

bool MemoryDatabase::remove_article(string name, string tit, string aut) {
    NewsGroup ng{*find_if(table.begin(), table.end(), [name](const NewsGroup& n) {return n.name == name;})};
    
    return ng.remove_article(tit, aut);
}
