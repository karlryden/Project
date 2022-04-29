#include "article.h"
//#include <functional>
using std::string;

unsigned int Article::count = 0;

using size_t = std::string::size_type;
Article::Article(const string& tit, const string& aut, const string& tex) : id(count++), title(tit), author(aut), text(tex) {}

string Article::to_string() const {
    return title + "|" + author + "|" + text;
}

bool Article::operator==(const Article& a) const{
    return (a.author == author) && (a.title == title);
}

string Article::get_author() const {
    return author;
}

string Article::get_title() const{
    return title;
}
//bool Article::operator==(const Article& a) const {
//    auto hasher{std::hash<Article>()};
//    return (hasher(*this) == hasher(a));
//}
