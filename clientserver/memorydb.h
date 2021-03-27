#include "database.h"
#include "newsgroup.h"

#ifndef MEMORYDB_H
#define MEMORYDB_H

class MemoryDatabase : public Database {
    public:
        std::string get_article(unsigned int, unsigned int) const;
        std::string get_newsgroup(unsigned int) const;
        bool set_newsgroup(std::string);
        bool set_article(unsigned int, std::string, std::string, std::string);
        bool remove_newsgroup(unsigned int);
        bool remove_article(unsigned int, unsigned int);
    private:
        std::vector<NewsGroup> table;
};

#endif