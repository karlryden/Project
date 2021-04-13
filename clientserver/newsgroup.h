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
        bool remove_article(const std::string&);
        std::string to_string() const;
        bool operator==(const NewsGroup&) const;
        Article make_article(const std::string&,  const std::string&, const std::string&);
    
        const unsigned int id;
    //
        std::vector::iterator begin();
        std::vector::iterator end();
        std::vector::size_type size();
        std::string get_title();
    private:
        const std::string title;
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
