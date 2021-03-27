#include "newsgroup.h"
#include <algorithm>

#include <iostream>

using std::string;
using std::find;

unsigned int NewsGroup::count = 0;

NewsGroup::NewsGroup(const string& n) : name(n), id(count++) {}

// Article NewsGroup::get_article(const unsigned int id) const {
    
//     return *find(ng.begin(), ng.end(), [id](const Article& a) {return a.id == id;});
// }

string NewsGroup::to_string() const {
    return "";
}
