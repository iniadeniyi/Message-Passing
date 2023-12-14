#include "server.hpp"



int setup_server(int port, int backlog)
{
    int server_socket;

    check((server_socket = socket(AF_INET, SOCK_STREAM, 0)), "Socket creation failed");
    printf("[+]Server socket created");
    // SET UP SERVER ADDRESS STRUCT
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(server_port); 

    check(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)), "Bind failed");
    printf("[+]Bind to port number: %d\n", port);
    check(listen(server_socket, backlog), "Listen failed");
    printf("Listening...\n");
    return server_socket;
}


int accept_new_cnxn(int server_socket)
{
    int addr_size = sizeof(sockaddr_in);
    int client_socket;
    sockaddr_in client_addr;
    check(client_socket = accept(server_socket, (struct sockaddr*)&client_addr, (socklen_t*)&addr_size), 
            "Accept failed");
    printf("Client connected\n");
    return client_socket;
}


void* handle_cnxn(int cnxn)
{
    size_t bytes_read;
    check( bytes_read = read(cnxn, rcv_buffer, MSG_SIZE), "Read failed");
    if (bytes_read == 0)
    {
        // IF THERE IS NO MESSAGE, CLOSE CONNECTION AND REMOVE FROM THE CONN ARRAY
        close(cnxn);
        FD_CLR(cnxn, &sockets);
    }
    else
    {
        // EXECUTE THE TRANSACTION RECEIVED FROM CLIENT
        char temp[MSG_SIZE]; char arg[MSG_SIZE];
        string client_name;
        check(sscanf(rcv_buffer, "%s %s", arg, temp), 
                        "Error: parsing request message failed\n");
        client_name = string(temp);
        
        log_trans_start(&s_log, atoi(arg), client_name);
        Trans(atoi(arg));
        log_trans_end(&s_log, client_name);

        // FILL THE SEND BUFFER WITH THE RESPONSE MESSAGE AND SEND IT
        snprintf((char *)send_buffer, MSG_SIZE, "%d", s_log.trans_count);
        if( size_t(send(cnxn, send_buffer, strlen(send_buffer), 0)) != strlen(send_buffer) ) 
        {
            perror("Write failed");
            exit(-1);
        }

    }
    return NULL;
}


int main(int argc, char *argv[])
{
    // HANDLE COMMAND LINE ARGUMENTS
    if ( argc < 2)
    {
        printf("\n Error: Missing port number");
        printf("\n Usage: %s <ip of server>\n", argv[0]);
        exit(-1);
    }
    server_port = atoi(argv[1]);
    validate_port_number(server_port);
    
    pid_t pid = getpid();
    server_name = get_entity_name(pid);

    listen_fd = setup_server(server_port, BACK_LOG);


    // INITIALIZE THE CURRENT SET
    FD_ZERO(&sockets);
    FD_SET(listen_fd, &sockets);


    int max_number_sockets = listen_fd;

    struct timeval timeout;

    int socket_count;
    init_server_logger(&s_log, server_port, server_name);
    while (true)
    {
        // copy socket since select is destructive
        fd_set sockets_copy = sockets;

        // Wait up to thirty seconds.
        timeout.tv_sec = 30;
        timeout.tv_usec = 0;

        check(socket_count = select(max_number_sockets+1, &sockets_copy, NULL, NULL, &timeout), "Select failed");
        if (socket_count == 0)
        {
            printf("timeout\n");
            break;
        }
        
        for (int i=0; i<(max_number_sockets+1); i++)
        {
            if (FD_ISSET(i, &sockets_copy))
            {
                if (i == listen_fd)
                {
                    // ACCEPT NEW CONNECTION
                    int new_cnxn = accept_new_cnxn(listen_fd);
                    FD_SET(new_cnxn, &sockets);
                    if (new_cnxn > max_number_sockets)
                    {
                        max_number_sockets = new_cnxn;
                    }
                }
                else
                {
                    // ACCEPT NEW MESSAGE
                    handle_cnxn(i);
                }
            }
        }

    }
    destroy_server_logger(&s_log);
    return 0;
}