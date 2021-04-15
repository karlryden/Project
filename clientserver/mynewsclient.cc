/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"

#include <cstdlib>
#include <iostream>

#include <stdexcept>
#include <string>
#include "protocol.h"
using namespace std;

/*
 * Send an integer to the server as four bytes.
 */
void writeNumber(const Connection& conn, int value)
{
        conn.write((value >> 24) & 0xFF);
        conn.write((value >> 16) & 0xFF);
        conn.write((value >> 8) & 0xFF);
        conn.write(value & 0xFF);
}
void writeString(const Connection& conn, const string& s){
    for (char c : s) {
        conn.write(c);
    }
}
void writeMsg(const Connection& conn, istream& in){
    int n;
    
    while (n != static_cast<int>(Protocol::COM_END)){
        in >> n;
        
        conn.write(n);
        if (n == static_cast<int>(Protocol::PAR_STRING)){
            in >> n;
            std::cout << n << std::endl;
            
            conn.write(n);
            char ch{};
            for (int i = 0; i < n; i++){
                in >> ch;
                conn.write(ch);
            }
        }
    }
    
}
/*
 * Read a string from the server.
 */
string readString(const Connection& conn)
{
        string s;
        char   ch;
        while ((ch = conn.read()) != '$') {
                s += ch;
        }
        return s;
}

/* Creates a client for the given args, if possible.
 * Otherwise exits with error code.
 */
Connection init(int argc, char* argv[])
{
        if (argc != 3) {
                cerr << "Usage: myclient host-name port-number" << endl;
                exit(1);
        }

        int port = -1;
        try {
                port = stoi(argv[2]);
        } catch (exception& e) {
                cerr << "Wrong port number. " << e.what() << endl;
                exit(2);
        }

        Connection conn(argv[1], port);
        if (!conn.isConnected()) {
                cerr << "Connection attempt failed" << endl;
                exit(3);
        }

        return conn;
}

int app(const Connection& conn)
{       
    while (true){
        std::cout << "Type a message: ";
        
        writeMsg(conn, cin);
        try {
                std::cout <<  " is ...";
                
                string reply = readString(conn);
                std::cout << " " << reply << endl;
                std::cout << "Type another message: ";
        } catch (ConnectionClosedException&) {
                std::cout << " no reply from server. Exiting." << endl;
                return 1;
        }
    }
        
        
        std::cout << "\nexiting.\n";
        return 0;
}

int main(int argc, char* argv[])
{
        Connection conn = init(argc, argv);
        return app(conn);
}
