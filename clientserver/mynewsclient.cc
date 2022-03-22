/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"

#include <cstdlib>

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "protocol.h"
#include "messagehandler.h"
#include "client.h"

using namespace std;
string MSG{"\nPick an action (enter number 0-7, 0 to quit): \n1. List newsgroups. \n2. Create newsgroup. \n3. Delete newsgroup. \n4. List articles in newsgroup. \n5. Create article. \n6. Delete article. \n7. Get article.\n"};

/*
 * Send an integer to the server as four bytes.
 */


void writeMsg(const Connection& conn, istream& in){
    int n;
    
    while (n != static_cast<int>(Protocol::COM_END)){
        in >> n;
        
        conn.write(n);
        if (n == static_cast<int>(Protocol::PAR_STRING)){
            in >> n;
            std::cout << n << std::endl;
            
            writeNumber(conn, n);
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
    int input{};
    string msg{};
    while (true){
        
        
        try {
                cout<<MSG<<endl;
                process_input(conn, input);
                if(input==0){
                cout<<"Exiting..."<<endl;
                break;
                }
                process_response(conn);
                
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
