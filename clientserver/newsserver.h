#include "server.h"
#include "database.h"

class NewsServer : public Server {
    public:
        NewsServer();
        NewsServer(Database);
        bool create_newsgroup(std::string);
        bool create_article(std::string, std::string, std::string, unsigned int);
        bool remove_newsgroup(unsigned int);
        bool remove_article(unsigned int, unsigned int);
        std::string list_newsgroups();
        std::string list_articles(unsigned int);
    private:
        Database db;
};