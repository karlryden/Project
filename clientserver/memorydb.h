#include "database.h"
#include "newsgroup.h"
#include <unordered_set>

class MemoryDatabase : public Database {
    public:
    private:
        std::unordered_set<NewsGroup> table;
};