#include "database.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

#ifndef DISKDB_H
#define DISKDB_H

/*

Note: Forbidden
en titel får ALDRIG innehålla tecknet som ges av delimiter eller
"art_count.txt" resp "ng_count.txt".

*/
class DiskDatabase : public Database {
    public:
        DiskDatabase();
        DiskDatabase(const std::string);
        std::string get_newsgroup(unsigned int) const;
        std::string get_article(unsigned int, unsigned int) const;
        bool set_newsgroup(std::string);
        bool set_article(unsigned int, std::string, std::string, std::string);
        bool remove_newsgroup(unsigned int);
        bool remove_article(unsigned int, unsigned int);
        std::string list_articles(unsigned int);
        std::string list_newsgroups();

        unsigned int getNewId();
        unsigned int getNewArtId(std::filesystem::path);
        std::filesystem::path get_newsgroup_path(unsigned int) const;
        std::filesystem::path get_article_path(unsigned int, unsigned int) const;
};

unsigned int ng_hash(std::string);
unsigned int art_hash(std::string, std::string);
#endif