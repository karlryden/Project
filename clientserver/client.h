#include "protocol.h"
#include "connectionclosedexception.h"
#include "connection.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "messagehandler.h"


int read_nbr();
void create_article(const Connection&);
void process_input(const Connection&, int&);
void delete_article(const Connection&);
void get_article(const Connection&);
void list(const Connection&);
void create(const Connection&);
void remove(const Connection&);
void get_art(const Connection&);
void process_response(const Connection&);