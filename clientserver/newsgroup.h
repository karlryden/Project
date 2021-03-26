#include "article.h"
#include <vector>

#ifndef NEWSGROUP_H
#define NEWSGROUP_H

class NewsGroup {
    public:
        NewsGroup(const std::string&);
        Article get_article(const unsigned int) const;
        bool set_article(const Article&);
        bool remove_article(const unsigned int);
        std::string to_string() const;
    private:
        const std::string name;
        std::vector<Article> ng;
        static unsigned int count;
        const unsigned int id;
};

#endif