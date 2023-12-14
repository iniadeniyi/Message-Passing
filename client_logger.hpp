#ifndef CLIENT_LOG_H
#define CLIENT_LOG_H 

#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>



using namespace std;
using namespace chrono;



typedef struct 
{
    int trans_count, port;
    string ip_addr;
    ofstream file;
    string filename;
    double time;
}   client_logger;


void init_client_logger(client_logger* log, int port, string client_name, char* ip_addr);
void destroy_client_logger(client_logger* log);
void calc_time(client_logger* log);
void log_sleep_comm(client_logger* log, int arg);
void log_trans_comm(client_logger* log, int arg);
void log_recv(client_logger* log, int res);


#endif