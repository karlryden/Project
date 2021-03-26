#include "database.h"
#include "newsgroup.h"

#ifndef MEMORYDB_H
#define MEMORYDB_H

class MemoryDatabase : public Database {
    public:
        set_article
    private:
        std::vector<NewsGroup> table;
};

#endif