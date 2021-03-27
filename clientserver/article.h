#include <string>
#include <ctime>

#ifndef ARTICLE_H
#define ARTICLE_H

class Article {
    public:
        Article(const std::string&, const std::string&, const std::string&);
        std::string to_string() const;       
        bool operator==(const Article&) const;
        const unsigned int id;

    private:
        const std::string title;
        const std::string author;
        const std::string text;
        static unsigned int count;
};

namespace std {
    template <> struct hash<Article> {
        typedef Article argument_type;
        typedef std::size_t result_type;

        result_type operator()(const Article& a) const {
            return a.id;
        }
    };
}

#endif