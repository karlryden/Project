
#ifndef MESSAGEHANDLER
#define MESSAGEHANDLER
#include "protocol.h"
#include "connection.h"
#include <string>
#include <memory>
#include <vector>
using std::shared_ptr;
using std::vector;

int readNumber(const Connection&);
std::string readString(const Connection&);
void writeString(const Connection&, const std::string&);
void writeNumber(const Connection&, int);

int readNumber(const shared_ptr<Connection>&);
std::string readString(const shared_ptr<Connection>&);
void writeString(const std::shared_ptr<Connection>&, const std::string&);
void writeNumber(const std::shared_ptr<Connection>&, int);

void get_request(const shared_ptr<Connection>&, int& comm, vector<int>& N, vector<std::string>& s, int& endbyte);
#endif