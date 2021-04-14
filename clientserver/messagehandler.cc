#include "messagehandler.h"
#include <iostream>
#include <vector>
using std::string;
using std::shared_ptr;
int readNumber(const shared_ptr<Connection>& conn){
    unsigned char byte1 = conn->read();
    std::cout << byte1 << std::endl;
    unsigned char byte2 = conn->read();
    std::cout << byte2 << std::endl;
    unsigned char byte3 = conn->read();
    std::cout << byte3 << std::endl;
    unsigned char byte4 = conn->read();
    std::cout << byte1 << byte2 << byte3 << byte4 << std::endl;
    return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}
string readString(const shared_ptr<Connection>& conn, int N){
    string s;
    for (int i = 0; i < N; i++){
        std::cout << s << std::endl;
        s += conn->read();
    }
    return s;
}

void get_request(const shared_ptr<Connection>& conn, int& command, std::vector<int>& N, std::vector<string>& s, int& end){
    command = conn->read();
    int n{conn->read()};
    int i{0};
    while (n != static_cast<int>(Protocol::COM_END)){
        
        
        if (n == static_cast<int>(Protocol::PAR_STRING)){
            n = conn->read();
            s.push_back(readString(conn, n));
        }
        else {
            n = conn->read();
            N.push_back(n);
        }
        n = conn->read();
    }
}