#include "newsgroup.h"
#include <string>

#ifndef DATABASE_H
#define DATABASE_H

class Database {
    public:
        virtual std::string get_newsgroup(unsigned int) const = 0;
        virtual std::string get_article(unsigned int, unsigned int) const = 0;
        virtual bool set_newsgroup(std::string) = 0;
        virtual bool set_article(std::string, std::string, std::string) = 0;
        virtual bool remove_newsgroup(unsigned int) = 0;
        virtual bool remove_article(unsigned int, unsigned int) = 0;
};

#endif