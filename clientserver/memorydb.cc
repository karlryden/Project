#include "memorydb.h"
#include <algorithm>

using std::string;
using std::find;

/*
- EJ FIXAT ERROR HANDLING I NÅGON FUNKTION!
- VET EJ HUR MAN SKA LÖSA find(NewsGroup) BARA UTIFRÅN ng_id.
*/

string MemoryDatabase::get_newsgroup(unsigned int ng_id) const {
    NewsGroup ng{*(table.find(ng_id))};
    // NewsGroup ng{*find(table.begin(), table.end(), [ng_id](const NewsGroup& n) {return n.id == ng_id;})};
    
    return ng.to_string();
}

string MemoryDatabase::get_article(size_t ng_id, size_t a_id) const {
    NewsGroup ng{*(table.find(ng_id))};
    // NewsGroup ng{*find(table.begin(), table.end(), [ng_id](const NewsGroup& n) {return n.id == ng_id;})};
    Article a{ng.get_article(a_id)};

    return a.to_string();
}

bool MemoryDatabase::set_newsgroup(std::string name) {
    NewsGroup ng(name);
    return (table.insert(ng)).second;
    // table.push_back(ng);
    
    return true;
}

bool MemoryDatabase::set_article(unsigned int ng_id, std::string tit, std::string aut, std::string tex) {
    NewsGroup ng{*(table.find(ng_id))};
    // NewsGroup ng{*find(table.begin(), table.end(), [ng_id](const NewsGroup& n) {return n.id == ng_id;})};
    Article a(tit, aut, tex);

    return ng.set_article(a);
}

bool MemoryDatabase::remove_newsgroup(unsigned int ng_id) {
    return table.erase(ng_id);
    // auto pos{find(table.begin(), table.end(), [ng_id](const NewsGroup& n) {return n.id == ng_id;})};
    // if (pos != table.end()) {
        // table.erase(pos);
        // return true;
    // }

    // return false;
}

bool MemoryDatabase::remove_article(unsigned int ng_id, unsigned int a_id) {
    NewsGroup ng{*find(table.begin(), table.end(), [ng_id](const NewsGroup& n) {return n.id == ng_id;})};
    
    return ng.remove_article(a_id);
}
