#include "article.h"
#include <vector>
#include <unordered_set>

#ifndef NEWSGROUP_H
#define NEWSGROUP_H

class NewsGroup {
    public:
        NewsGroup(const std::string&);
        Article get_article(const unsigned int) const;
        bool set_article(const Article&);
        bool remove_article(const unsigned int);
        std::string to_string() const;
        friend struct std::hash<NewsGroup>;

    private:
        const std::string name;
        std::unordered_set<Article> ng;
        static unsigned int count;
        const unsigned int id;
};

namespace std {
    template <> struct hash<NewsGroup> {
        size_t operator()(const NewsGroup& ng) const {
            return ng.id;
        }
    };
}

#endif