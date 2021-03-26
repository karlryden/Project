#include <string>
#include <ctime>

#ifndef ARTICLE_H
#define ARTICLE_H

class Article {
    public:
        Article(const std::string&, const std::string&, const std::string&);
        std::string to_string() const;       
        bool operator==(const Article&); 
    private:
        const std::string title;
        const std::string author;
        const std::string text;
        static unsigned int count;
        const unsigned int id;        
};

#endif