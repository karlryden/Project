#include "newsgroup.h"

using std::string;

unsigned int NewsGroup::count = 0;

NewsGroup::NewsGroup(const string& n) : name(n), id(count++) {}

Article NewsGroup::get_article(const unsigned int id) const {
    return ng
}

string NewsGroup::to_string() const {
    return "";
}

