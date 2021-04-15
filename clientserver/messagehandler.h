#include "protocol.h"
#include "connection.h"
#include <string>
#include <memory>
#include <vector>
using std::shared_ptr;
using std::vector;
int readNumber(const shared_ptr<Connection>&);

std::string readString(const shared_ptr<Connection>&);

void get_request(const shared_ptr<Connection>&, int& comm, vector<int>& N, vector<std::string>& s, int& endbyte);