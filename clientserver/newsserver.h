#include "server.h"
#include "database.h"


class NewsServer : public Server {
    public:
        NewsServer(Database);
        bool create_newsgroup(?);
        bool create_article(?, ?);
        bool remove_newsgroup(?);
        bool remove_article(?);
        ? list_newsgroups();
        ? list_articles(?);
    private:
        Database db;
};