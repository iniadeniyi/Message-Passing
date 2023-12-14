#include "client_logger.hpp"

void init_client_logger(client_logger* log, int port, string client_name, char* ip_addr)
{
    log->port = port;
    log->ip_addr = ip_addr;
    log->trans_count = 0;

    // CREATE FILE
    log->filename = client_name + ".log";
    log->file.open(log->filename);
    if(!log->file.is_open())
    {
        perror("Unable to create file.\n");
        exit(-1);
    }
    // LOG INITIAL MESSAGE INTO THE FILE
    log->file << "Using port " << log->port << endl;
    log->file << "Using server address " << log->ip_addr << endl;
    log->file << "Host " << client_name << endl << endl;
}

void destroy_client_logger(client_logger* log)
{
    // LOG THE FINAL INFORMATION AND CLOSE LOG FILE
    if (log->trans_count == 1)
    {
        log->file << "Sent " << log->trans_count << " transaction" << endl;
    } 
    else 
    {
        log->file << "Sent " << log->trans_count << " transactions" << endl;
    }
    log->file.close();
}

void calc_time(client_logger* log)
{
    log->time = (double)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() / (double)1000;
}

void log_sleep_comm(client_logger* log, int arg)
{
    log->file << "Sleep " << arg << " units" << endl;
}

void log_trans_comm(client_logger* log, int arg)
{
    calc_time(log);
    log->trans_count++;
    log->file << fixed << setprecision(2) << log->time << ":\tSend (T " << setw(3) << arg << ")" << endl; 
}

void log_recv(client_logger* log, int res)
{
    calc_time(log);
    log->file << fixed << setprecision(2) << log->time << ":\tRecv (D " << setw(3) << res << ")" << endl;
}