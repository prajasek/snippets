#include <sys/types.h> //size_t
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include "getaddr.h"


int main(int argc, char* argv[]){

    /* 
        Usage : ./run_server <port_number_to_bind> 
        example: ./run_server 80
    */

    char* PORT = "8080" ;
    if (argc>1) {
        PORT = argv[1];
    }
    printf("Port  : %s\n", PORT);
    int server_or_client = AI_PASSIVE; //AI_PASSIVE - server;  0 - client
    struct addrinfo* result = getaddr(NULL, PORT, server_or_client );
    int sockfd; 

    sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (argc < 2 && server_or_client == AI_PASSIVE) {
        bind(sockfd, result->ai_addr, result->ai_addrlen);
    }

    freeaddrinfo(result);
    

    
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