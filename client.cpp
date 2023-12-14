#include "client.hpp"

int setup_client(int port, char* ip_addr)
{
    int client_socket;

    check((client_socket = socket(AF_INET, SOCK_STREAM, 0)), "Socket creation failed");
    printf("Socket created.\n");
    // SET UP SERVER ADDRESS STRUCT
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port); 
    // client_addr.sin_addr.s_addr = inet_addr(ip_addr); 
    check(inet_pton(AF_INET, ip_addr, &client_addr.sin_addr), "inet_pton failed");

    check(connect(client_socket, (struct sockaddr *)&client_addr, sizeof(client_addr)), "Connection failed");
    printf("Connected to server.\n");
    return client_socket;
}


int main(int argc, char *argv[])
{
    // HANDLE COMMAND LINE ARGUMENTS
    if ( argc < 3)
    {
        printf("\n Error: Missing port number");
        printf("\n Usage: %s <ip of server>\n", argv[0]);
        exit(-1);
    }
    client_port = atoi(argv[1]);
    ip_addr = argv[2];
    validate_port_number(client_port);

    pid_t pid = getpid();
    client_name = get_entity_name(pid);

    int sock_fd = setup_client(client_port, ip_addr);

    // INITIALIZE THE LOGGER FOR THE CLIENT OPERATIONS
    client_logger c_log;
    init_client_logger(&c_log, client_port, client_name, ip_addr);

    string line;
    while (getline(cin, line))
    {
        // SLEEP CLIENT
        if (line[0] == 'S')
        {
            line.erase(0, 1);
            int arg_i = stoi(line);
            Sleep(arg_i);
            log_sleep_comm(&c_log, arg_i);
        }
        else if (line[0] == 'T')
        {
            // SEND TRANSACTION TO SERVER
            line.erase(0, 1);
            int arg_i = stoi(line), trans_id=0;
            memset(send_buffer, '0', sizeof(send_buffer));
            string msg = line + " " + client_name;
            strcpy(send_buffer, msg.c_str());
            check(send(sock_fd, send_buffer, sizeof(send_buffer), 0), "Send failed");
            log_trans_comm(&c_log, arg_i);

            check(recv(sock_fd, rcv_buffer, MSG_SIZE, 0), "Read failed");
            check(sscanf(rcv_buffer, "%d\n", &trans_id), "Read from buffer failed");
            log_recv(&c_log, trans_id);
        }
    }
    destroy_client_logger(&c_log);
    return 0;
}