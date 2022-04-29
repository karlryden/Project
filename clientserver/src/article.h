#include <string>
#include <ctime>

#ifndef ARTICLE_H
#define ARTICLE_H

class Article {
    public:
        Article(const std::string&, const std::string&, const std::string&);
        std::string to_string() const;       
        bool operator==(const Article&) const;
        std::string get_author() const;
        std::string get_title() const;
        unsigned int id;
        
    private:
        std::string title;
        std::string author;
        std::string text;
        static unsigned int count;
};

// namespace std {
//     template <> struct hash<Article> {
//         typedef Article argument_type;
//         typedef std::size_t result_type;

//         result_type operator()(const Article& a) const {
//             return a.id;
//         }
//     };
// }

#endif
