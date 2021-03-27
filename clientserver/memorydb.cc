#include "memorydb.h"
#include <algorithm>

using std::string;
using std::find;
using std::to_string;

/*
- EJ FIXAT ERROR HANDLING I NÅGON FUNKTION!
- VET EJ OM DET ÄR BRA ATT HA VECTOR EFTERSOM VÅRA GET METODER BLIR BAJS OCH VI KOMMER INTE ÅT id I LAMBDA,
  KANSKE BÄTTRE ATT KÖRA unordered_set ÄNDÅ?
- VÄRT ATT LÄGGA TILL INTERNA GETTERS OCH SETTERS SOM RETURNERAR NewsGroup och Article
  EFTERSOM VI ÅTERANVÄNDER find HELA TIDEN?
- ELLER KANSKE BARA LÄGGA TILL find_newsgroup OCH find_article?
*/

string MemoryDatabase::get_newsgroup(unsigned int ng_id) const {
    NewsGroup ng{*find(table.begin(), table.end(), [ng_id](const NewsGroup& n) {return n.id == ng_id;})};
    
    return to_string(ng);
}

string MemoryDatabase::get_article(unsigned int ng_id, unsigned int a_id) const {
    NewsGroup ng{*find(table.begin(), table.end(), [ng_id](const NewsGroup& n) {return n.id == ng_id;})};
    Article a{ng.get_article(a_id)};

    return to_string(a);
}

bool MemoryDatabase::set_newsgroup(std::string name) {
    NewsGroup ng(name);
    table.push_back(ng);
    
    return true;
}

bool MemoryDatabase::set_article(unsigned int ng_id, std::string tit, std::string aut, std::string tex) {
    Article a(tit, aut, tex);
    NewsGroup ng{*find(table.begin(), table.end(), [ng_id](const NewsGroup& n) {return n.id == ng_id;})};
    ng.set_article(a);

    return true;
}

bool MemoryDatabase::remove_newsgroup(unsigned int ng_id) {
    auto pos{find(table.begin(), table.end(), [ng_id](const NewsGroup& n) {return n.id == ng_id;})};
    if (pos != table.end()) {
        table.erase(pos);
        return true;
    }

    return false;
}

bool MemoryDatabase::remove_article(unsigned int ng_id, unsigned int a_id) {
    NewsGroup ng{*find(table.begin(), table.end(), [ng_id](const NewsGroup& n) {return n.id == ng_id;})};
    
    return ng.remove_article(a_id);
}
