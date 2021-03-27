#include "article.h"
#include <functional>
using std::string;

unsigned int Article::count = 0;

using size_t = std::string::size_type;
Article::Article(const string& tit, const string& aut, const string& tex) : 
                title(tit), author(aut), text(tex), id(count++) {}

string Article::to_string() const {
    return "";
}

bool Article::operator==(const Article& a) const {
    auto hasher{std::hash<Article>()};
    return (hasher(*this) == hasher(a));
}