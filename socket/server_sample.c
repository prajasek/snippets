#include <sys/types.h> //size_t
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>   // inet_pton
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>  //int errno  -- global variable
#include "getaddr.h"

int main(int argc, char* argv[]){

    /* 
        Usage : ./run_server <port_number_to_bind> 
        example: ./run_server 80
    */
    struct sockaddr_storage* peer_address;
    char* PORT =  "8080" ;
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
    
    listen(sockfd, 1);

    printf("\nWaiting for connection at port : %hu\n", ntohs(((struct sockaddr_in*)result->ai_addr)->sin_port));

    socklen_t addr_size = sizeof peer_address;

    FILE* infile = fopen("input.txt", "r");

    while (true) {
        printf("\nWaiting...\n");
        newfd = accept(sockfd, (struct sockaddr*)&peer_address, &addr_size);
        FILE* file = fopen("output.txt", "w");

        char ip_src[INET_ADDRSTRLEN];
        struct in_addr* src_in_addr = &(((struct sockaddr_in*)&peer_address)->sin_addr);

        inet_ntop(AF_INET, src_in_addr, ip_src, INET_ADDRSTRLEN);

        printf("New connection : %s\n", ip_src);
        printf("New fd: %d\n", newfd);
        
        char msg_buffer[1000]; 
        int x1; 

        fseek(infile,0, SEEK_SET);
        memset(msg_buffer, 1000, 0);
        while ((x1=recv(newfd, msg_buffer, 1000, 0)) > 0) {
            printf("Bytes Received -- %d\n", x1 );
            printf("Message received : %s\n", msg_buffer);
            fwrite(msg_buffer, 1, 1000, file);
            //fputs(msg_buffer, file);
            // Sending back message:
            printf("after fwrite");
            char* read_query = "getfile";
            if (strcmp(read_query, msg_buffer)==0) {
                fseek(infile,0, SEEK_SET);
            }

            memset(msg_buffer, 0, 1000);
            char file_msg[1000];
            char* delimiter = "----------xyzEOF";
            while (!feof(infile)){
                fgets(file_msg, 1000, infile);
                printf("Sending : %s\n", file_msg);
                send(newfd, file_msg, strlen(file_msg), 0);
            } 
            send(newfd, delimiter, strlen(delimiter), 0);
            printf("x1 : %d\n", x1);
        }
        printf("Exiting : %d", x1);
        fclose(file);
        close(newfd);
    }
    

//    freeaddrinfo(result);
    printf("Closing...\n");

    
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