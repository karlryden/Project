#include "database.h"
#include "newsgroup.h"
#include <unordered_set>

#ifndef MEMORYDB_H
#define MEMORYDB_H

class MemoryDatabase : public Database {
    public:
        set_article
    private:
        std::unordered_set<NewsGroup> table;
};

#endif