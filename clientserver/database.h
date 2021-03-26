#include "newsgroup.h"
#include <string>

class Database {
    public:
        virtual Article get_article(unsigned int, unsigned int) = 0;
        virtual NewsGroup get_newsgroup(unsigned int) = 0;
        virtual bool set_article(?, ?) = 0;
        virtual bool set_newsgroup(?, ?) = 0;
        virtual bool remove_article(unsigned int, unsigned int) = 0;
        virtual bool remove_newsgroup(unsigned int, unsigned int) = 0;
};