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

int main() {
    std::unordered_set<Article> us{};
    Article a1{"t1", "a1", ""};
    Article a2{"t2", "a2", ""};
    Article a3{"t3", "a3", ""};
    
    us.insert(a1);
    us.insert(a2);
    us.insert(a3);

    for (auto a : us) {
        std::cout << typeid(a.id).name() << std::endl;
    }
}