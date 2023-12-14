#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <limits.h>
#include <sys/types.h>


using namespace std;


#define MIN_PORT_NUM 5000
#define MAX_PORT_NUM 64000
#define MSG_SIZE 1024


void validate_port_number(int port_num);
string get_entity_name(pid_t pid);
int check(int expression, const char * msg);