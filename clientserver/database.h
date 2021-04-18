#include "newsgroup.h"
#include <string>

#ifndef DATABASE_H
#define DATABASE_H

class Database {
    public:
        // returnar tom sträng om article/newsgroup not found
        // newsgroup: id namn
        virtual std::string get_newsgroup(unsigned int) const = 0;

        // article: title|author|text
        virtual std::string get_article(unsigned int, unsigned int) const = 0;
        virtual bool set_newsgroup(std::string) = 0;
        virtual bool set_article(unsigned int, std::string, std::string, std::string) = 0;
        virtual bool remove_newsgroup(unsigned int) = 0;
        virtual bool remove_article(unsigned int, unsigned int) = 0;

        //lista:  antal id längd titel id längd titel
        virtual std::string list_articles(unsigned int) = 0;
        virtual std::string list_newsgroups() = 0;
};

#endif