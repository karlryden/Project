#include "article.h"

using std::string;

unsigned int Article::count = 0;

Article::Article(const string& tit, const string& aut, const string& tex) : 
                title(tit), author(aut), text(tex), id(count++) {}

string Article::to_string() const {
    return "";
}
