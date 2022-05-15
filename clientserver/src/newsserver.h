#include "server.h"
#include "database.h"
#include "protocol.h"
#include <memory>
#include "connection.h"
#include "messagehandler.h"
#include "sstream"
#ifndef NEWSSERVER_H
#define NEWSSERVER_H

class NewsServer : public Server {
    public:
        NewsServer(int, bool);
        
        std::string get_newsgroup(unsigned int);
        std::string get_article(unsigned int, unsigned int);
        bool create_newsgroup(std::string);
        bool create_article(unsigned int, std::string, std::string, std::string);
        bool remove_newsgroup(unsigned int);
        bool remove_article(unsigned int, unsigned int);
        std::string list_newsgroups();
        std::string list_articles(unsigned int);
        std::string handle_request(const std::shared_ptr<Connection>&);
    private:
        std::unique_ptr<Database> db;
};

#endif
