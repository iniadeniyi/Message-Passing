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
#include "server_logger.hpp"



#define BACK_LOG 10
#define MSG_SIZE 1024


int server_port;
string server_name;
struct sockaddr_in server_addr; 

int listen_fd;
server_logger s_log;
fd_set sockets;
char rcv_buffer[MSG_SIZE];
char send_buffer[MSG_SIZE];
extern void Trans( int n );





