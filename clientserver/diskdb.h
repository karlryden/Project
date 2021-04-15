#include "database.h"
#include <string>
#include <experimental/filesystem>
#include <fstream>

#ifndef DISKDB_H
#define DISKDB_H

class DiskDatabase : public Database {
    public:
        DiskDatabase();
        DiskDatabase(const std::string);
        std::string get_newsgroup(unsigned int) const;
        std::string get_article(unsigned int, unsigned int) const;
        bool set_newsgroup(std::string);
        bool set_article(unsigned int, std::string, std::string, std::string);
        bool remove_newsgroup(unsigned int) = 0;
        bool remove_article(unsigned int, unsigned int);
        std::string list_articles(unsigned int);
        std::string list_newsgroups();

    private:
        std::experimental::filesystem::recursive_directory_iterator iter;
};

#endif