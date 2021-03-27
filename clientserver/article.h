#include <string>
#include <ctime>

#ifndef ARTICLE_H
#define ARTICLE_H

class Article {
    public:
        Article(const std::string&, const std::string&, const std::string&);
        std::string to_string() const;       
        bool operator==(const Article&) const;
        friend struct std::hash<Article>;

    private:
        const std::string title;
        const std::string author;
        const std::string text;
        static unsigned int count;
        const unsigned int id;
        
        std::string::size_type hashcode() const;
};

namespace std {
    template <> struct hash<Article> {
        size_t operator()(const Article& a) const {
            return a.id;
        }
    };
}

#endif