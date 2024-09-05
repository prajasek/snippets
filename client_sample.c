#include <sys/types.h> //size_t
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include "getaddr.h"


int main(int argc, char* argv[]){

     /* 
        Usage : ./run_client <address | localhost> <port | 8080>
        example: ./run_client www.google.com 80
    */

    char* ADDRESS = NULL; // localhost
    char* PORT = "8080";

    if (argc > 2) {
        ADDRESS = argv[1];   
        PORT = argv[2];      
    } else {
        printf("---- Connecting to localhost 8080.....\n\n");
    }
    
    printf("Address Input: %s\n", ADDRESS);
    printf("Port/Service input: %s\n", PORT);

    int server_or_client = 0; //AI_PASSIVE - server;  0 - client
    struct addrinfo* result = getaddr(ADDRESS, PORT, server_or_client);
    int sockfd; 

    // result is the head of a linked list. 
    // but we are just connecting to the first result. 
    sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    int err = connect(sockfd, result->ai_addr, result->ai_addrlen );

    if (err!=0) {
        fprintf(stderr, "Failed connecting. \nExiting..\n\n");
        exit(1);
    } else {
        printf("****** Connection Success! *********** \n\n");
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