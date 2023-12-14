#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include "utility.hpp"
#include "client_logger.hpp"

#define MSG_SIZE 1024



using namespace std;


int client_port;
char * ip_addr;
string client_name;
struct sockaddr_in client_addr; 
char rcv_buffer[MSG_SIZE];
char send_buffer[MSG_SIZE];
extern void Sleep( int n );
