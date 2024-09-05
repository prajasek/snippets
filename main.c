#include <sys/types.h> //size_t
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include "getaddr.h"


int main(int argc, char* argv[]){
    char* value = argv[1];
    printf("input: %s", value);
    struct addrinfo* result = getaddr(argv[1]);
    int sock; 

    sock = socket(AF_INET, SOCK_STREAM, 0);
    printf ("socket fd: %d", sock);

}