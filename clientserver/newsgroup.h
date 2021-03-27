#include "article.h"
#include <vector>
#include <unordered_set>

#ifndef NEWSGROUP_H
#define NEWSGROUP_H

class NewsGroup {
    public:
        NewsGroup(const std::string&);
        Article get_article(std::string, std::string) const;
        bool set_article(const Article&);
        bool remove_article(std::string, std::string);
        std::string to_string() const;
        bool operator==(const NewsGroup&) const;
        const unsigned int id;

    private:
        const std::string name;
        std::vector<Article> ng;
        // std::unordered_set<Article> ng;
        static unsigned int count;
};

// namespace std {
//     template <> struct hash<NewsGroup> {
//         std::size_t operator()(const NewsGroup& ng) const {
//             return std::hash<int>()(ng.id);
//         }
//     };
// }

#endif