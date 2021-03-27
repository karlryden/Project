#include "database.h"
#include "newsgroup.h"

#ifndef MEMORYDB_H
#define MEMORYDB_H

class MemoryDatabase : public Database {
    public:
        std::string get_newsgroup(std::string) const;
        std::string get_article(std::string, std::string, std::string) const;
        bool set_newsgroup(std::string);
        bool set_article(std::string, std::string, std::string, std::string);
        bool remove_newsgroup(std::string);
        bool remove_article(std::string, std::string, std::string);
    private:
        std::vector<NewsGroup> table;
        // std::unordered_set<NewsGroup> table;
};

#endif