#include "article.h"

class NewsGroup {
    public:
        static int count;
    private:
        std::unordered_set<Article> ng;
};