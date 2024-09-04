#include <sys/types.h> //size_t
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include "getaddr.h"


int main(int argc, char* argv[]){
    struct addrinfo* result = getaddr(argv[1]);
    printf("Address of first entry: %s\n", result->ai_canonname);
}