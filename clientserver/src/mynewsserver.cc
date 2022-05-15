#include "connection.h"
#include "connectionclosedexception.h"
#include "server.h"
#include "newsserver.h"
#include "protocol.h"
#include "messagehandler.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
/*
* Read an integer from a client.
*/

/*
* Read a string of length N form client.
*/

/*
* Send a string to a client.
* FIX: Send reply to client
*/
void writeString_noProtocol(const shared_ptr<Connection>& conn, const string& s){
    for (char c : s) {
        conn->write(c);
    }
    conn->write('$');
}

/*
* initialize server
*/
NewsServer init(int argc, char* argv[]){
    if (argc != 3) {
        cerr << "Usage: myserver port-number database-type" << endl;
        exit(1);
    }
    int port = -1;
    bool use_disk = false;
    try {
        port = stoi(argv[1]);
    } catch (exception& e) {
        cerr << "Wrong format for port number. " << e.what() << endl;
        exit(2);
    }
    try {
        string arg(argv[2]);
        if (arg.compare("diskdatabase") == 0) {
            use_disk = true;
        } else if (arg.compare("memorydatabase") == 0) {
            use_disk = false;
        } else {
            cerr << "Valid databse types: diskdatabase, memorydatabase" << endl;
            exit(2);
        }
    } catch (exception& e) {
        cerr << "Wrong format for port number. " << e.what() << endl;
        exit(2);
    }
    NewsServer server(port, use_disk);
    if (!server.isReady()) {
        cerr << "Server initialization error." << endl;
        exit(3);
    }
    return server;
}


/*
* Run server
*/
int main(int argc, char* argv[]){
    auto server = init(argc, argv);
    string result;
    while (true) {
        auto conn = server.waitForActivity();
        if (conn != nullptr) {
            try {
                vector<string> s;
                vector<int> N{};
                
                server.handle_request(conn);
                
            } catch (ConnectionClosedException&) {
                server.deregisterConnection(conn);
                cout << "Client closed connection" << endl;
            }
        } else {
            conn = make_shared<Connection>();
            server.registerConnection(conn);
            cout << "New client connects" << endl;
        }
    }
    return 0;
}