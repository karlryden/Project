#include "database.h"
#include <string>
#include <iostream>
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
        bool remove_newsgroup(unsigned int);
        bool remove_article(unsigned int, unsigned int);
        std::string list_articles(unsigned int);
        std::string list_newsgroups();

        unsigned int getNewId();
        unsigned int getNewArtId(unsigned int);
};

unsigned int ng_hash(std::string);
unsigned int art_hash(std::string, std::string);

std::string ng_string(std::experimental::filesystem::directory_entry);
std::string art_string(std::experimental::filesystem::directory_entry);

#endif