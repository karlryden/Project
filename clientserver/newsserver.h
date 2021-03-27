#include "server.h"
#include "database.h"
#include "messagehandler.h"

#ifndef NEWSSERVER_H
#define NEWSSERVER_H

class NewsServer : public Server {
    public:
        NewsServer();
        NewsServer(Database&);
        std::string get_newsgroup(std::string);
        std::string get_article(std::string, std::string, std::string);
        bool create_newsgroup(std::string);
        bool create_article(std::string, std::string, std::string, std::string);
        bool remove_newsgroup(std::string);
        bool remove_article(std::string, std::string, std::string);
        std::string list_newsgroups();
        std::string list_articles(std::string);
        bool handle_request();
    private:
        Database& db;
        MessageHandler mh;
};

#endif