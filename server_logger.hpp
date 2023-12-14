#ifndef SERVER_LOG_H
#define SERVER_LOG_H 

#include <iostream>
#include <fstream>
#include <chrono>
#include <map>
#include <iomanip>


using namespace std;
using namespace chrono;

typedef struct 
{
    int trans_count, port;
    pid_t pid;
    char* host_name;
    ofstream file;
    string filename;
    map<string, int> client_trans;
    ofstream server_file;
    double curr_time, start_time;
}   server_logger;


void init_server_logger(server_logger* log, int port, string server_name);
void destroy_server_logger(server_logger* log);
void calc_time(server_logger* log);
void log_trans_start(server_logger* log, int arg, string client_name);
void log_trans_end(server_logger* log, string client_name);


#endif