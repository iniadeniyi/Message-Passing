#include "server_logger.hpp"
void init_server_logger(server_logger* log, int port, string server_name)
{
    log->trans_count = 0;
    log->start_time = 0;
    // CREATE FILE
    log->filename = "server.log";
    log->file.open(log->filename);
    if(!log->file.is_open())
    {
        perror("Unable to create file.\n");
        exit(-1);
    }

    // LOG INITIAL MESSAGE INTO THE FILE
    log->file << "Using port " << port << endl;
}

void destroy_server_logger(server_logger* log )
{
    int total_trans = 0;
    log->file << "SUMMARY" << endl;
    for(map<string, int>::const_iterator it = log->client_trans.begin();
    it != log->client_trans.end(); ++it)
    {
        log->file << setw(5) << "\t" << it->second << " transactions from " << it->first << endl;
        total_trans += it->second;
    }
    double trans_per_sec = total_trans/(log->curr_time - log->start_time);
    log->file << setw(4) << fixed << setprecision(1) << trans_per_sec << " transactions/sec (" << total_trans << "/" << fixed << setprecision(2) << log->curr_time - log->start_time << ")";
    log->file.close();
}

void calc_time(server_logger* log)
{
    log->curr_time = (double)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() / (double)1000;
}

void log_trans_start(server_logger* log, int arg, string client_name) 
{   
    log->trans_count++;
    calc_time(log);
    if (log->trans_count == 1)
    {
        log->start_time = log->curr_time;
    }
    log->file << fixed << setprecision(2) << log->curr_time << ": # " << log->trans_count << "\t(T" << setw(3) << arg << ")" << "\tfrom " << client_name << endl;
}

void log_trans_end(server_logger* log, string client_name)
{
    calc_time(log);
    log->file << fixed << setprecision(2) << log->curr_time << ": # " << log->trans_count << "\t(Done)" << "\tfrom " << client_name << endl;
    
    // UPDATE THE CLIENT-TRANSACTION MAP
    map<string, int>::iterator it = log->client_trans.find(client_name);
    if (it != log->client_trans.end()) 
    {
        it->second++;
    } 
    else 
    {
        log->client_trans[client_name] = 1;
    }
}


