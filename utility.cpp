#include "utility.hpp"

void validate_port_number(int port_num)
{
    if (port_num<MIN_PORT_NUM || port_num > MAX_PORT_NUM)
    {
        printf("\nError: Port number out of range!");
        printf("\nPort number should be between %d and %d\n", MIN_PORT_NUM, MAX_PORT_NUM);
        exit(-1);
    }
}

string get_entity_name(pid_t pid)
{
    char machine_name[HOST_NAME_MAX];
    if (gethostname(machine_name, HOST_NAME_MAX) < 0) 
    {
        printf("\nError: failed to get host name\n");
        exit(-1);
    }
    string entity_name = string(machine_name) + "." + to_string(pid);
    return entity_name;
}

int check(int expression, const char * msg)
{
    if (expression < 0)
    {
        perror(msg);
        exit(-1);
    }
    return expression;
}