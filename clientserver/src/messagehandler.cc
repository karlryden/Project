#include "messagehandler.h"
#include <iostream>
#include <vector>
using std::string;
using std::shared_ptr;
using std::cout;
using std::endl;

void write4b(const shared_ptr<Connection>& conn, int N){
    conn->write((N >> 24) & 0xFF);
    conn->write((N >> 16) & 0xFF);
    conn->write((N >> 8) & 0xFF);
    conn->write(N & 0xFF);
    

}

void write4b(const Connection& conn, int N){
    conn.write((N >> 24) & 0xFF);
    conn.write((N >> 16) & 0xFF);
    conn.write((N >> 8) & 0xFF);
    conn.write(N & 0xFF);
}

int readNumber(const shared_ptr<Connection>& conn){
    
    unsigned char byte1 = conn->read();
    unsigned char byte2 = conn->read();
    unsigned char byte3 = conn->read();
    unsigned char byte4 = conn->read();
    return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

int readNumber(const Connection& conn){
    unsigned char byte1 = conn.read();
    unsigned char byte2 = conn.read();
    unsigned char byte3 = conn.read();
    unsigned char byte4 = conn.read();
    return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

void writeNumber(const Connection& conn, int N)
{
    write4b(conn, N);
}

void writeNumber(const shared_ptr<Connection>& conn, int N){
    
    write4b(conn, N);
}
void writeString(const shared_ptr<Connection>& conn, const string& s){
    
    writeNumber(conn, s.size());
    for (unsigned char ch: s){
        conn->write(ch);
    }
}
void writeString(const Connection& conn, const string& s){
    
    writeNumber(conn, s.size());
    for (unsigned char c : s) {
        conn.write(c);
        cout << c << endl;
    }
}

string readString(const Connection& conn){
    string s;
    int N{readNumber(conn)};
    for (int i = 0; i < N; i++){
        s += conn.read();
    }
    return s;
}


string readString(const shared_ptr<Connection>& conn){
    string s;
    int N{readNumber(conn)};
    for (int i = 0; i < N ; i++){
        s += conn->read();
    }
    return s;
}




