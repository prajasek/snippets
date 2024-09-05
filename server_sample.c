#include <sys/types.h> //size_t
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include "getaddr.h"


int main(int argc, char* argv[]){
    char* ADDRESS = argv[1];
    char* PORT = "80";
    printf("input: %s", ADDRESS);
    int server_or_client = AI_PASSIVE; //AI_PASSIVE - server;  0 - client
    struct addrinfo* result = getaddr(argv[1],PORT, server_or_client );
    int sock; 

    sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    printf("socket fd: %d\n", sock);
    if (argc < 2 && server_or_client == AI_PASSIVE) {
        bind(sock, result->ai_addr, result->ai_addrlen);
    }
    /* OLD WAY OF PACKING SOCKADDR_IN FOR BINDING. USE getaddrinfo()
        struct sockaddr_in my_addr; 
        sock = socket(AF_INET, SOCK_STREAM, 0);
        my_addr.sin_family = AF_INET;
        my_addr.sin_port = htons(8000);
        my_addr.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY==0.0.0.0
        memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);
        
        bind(sock, (struct sockaddr*)&my_addr, sizeof my_addr);
    */
    
    freeaddrinfo(result);
    

    
}