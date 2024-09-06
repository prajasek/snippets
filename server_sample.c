#include <sys/types.h> //size_t
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>  //int errno  -- global variable
#include "getaddr.h"

int main(int argc, char* argv[]){

    /* 
        Usage : ./run_server <port_number_to_bind> 
        example: ./run_server 80
    */
    struct sockaddr_storage* peer_address;
    char* PORT =  "8123" ;
    int sockfd; 
    int newfd;
    int server_or_client = AI_PASSIVE; //AI_PASSIVE - server;  0 - client
    int yes=1;
    if (argc>1) {
        PORT = argv[1];
        printf("porting : %s \n", PORT);
    }
    printf("Port: <%s>\n", PORT);

    struct addrinfo* result = getaddr(NULL, PORT, server_or_client );
    sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    printf("Socket Created : %d ", sockfd );
    // set socket option
    if (setsockopt(sockfd, SOL_SOCKET,SO_REUSEADDR, &yes, sizeof yes) == -1) {
        printf("Error Sockopt");
        exit(1);
    }
    //bind
    if (argc < 2 && server_or_client == AI_PASSIVE) {
        bind(sockfd, result->ai_addr, result->ai_addrlen);
    }
    
    listen(sockfd, 10);
    short int rrr = ntohs(((struct sockaddr_in*)result->ai_addr)->sin_port);
    printf("\nCHECK PORT NUMBER: %hu\n", ntohs(((struct sockaddr_in*)result->ai_addr)->sin_port));

    socklen_t addr_size = sizeof peer_address;
    newfd = accept(sockfd, (struct sockaddr*)&peer_address, &addr_size);
    printf("Newfd: %d %d\n", newfd, rrr);
    printf("New connection : %u\n", ((struct sockaddr_in*)&peer_address)->sin_addr.s_addr);

    freeaddrinfo(result);
    printf("Closing...\n");
    close(sockfd);
    
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