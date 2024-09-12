#include <netdb.h>       // getaddrinfo
#include <arpa/inet.h>   // inet_pton
#include <sys/socket.h>  // socket
#include <sys/types.h>   // size_t
#include <stdio.h>       // printf
#include <string.h>      // strcpy
#include <stdint.h>      // uint32_t
#include <stdlib.h> 



struct addrinfo* getaddr(char* address, char* PORT, int ai_flags) 
{
    struct addrinfo             hints; 
    struct addrinfo             *result, *rp; 
    struct sockaddr_storage     peer_addr; 
    char ipstr[INET6_ADDRSTRLEN];
    char* input_address = NULL;
    if (address) 
    {
        input_address = address;
    }

    printf("Getting addrinfo for: %s \nPort: %s\n\n ", input_address, PORT);

    memset(&hints, 0, sizeof hints);
    
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = ai_flags; 
    hints.ai_protocol = 0; 

    int status = getaddrinfo(input_address, PORT, &hints, &result);
    if (status!=0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(1);
    }
    
    for (rp=result; rp!=NULL; rp = rp->ai_next) {
        void* addr; 
        char* ipver;
        unsigned short port4=0, port6=0; 
        struct sockaddr_in *ip4;
        struct sockaddr_in6* ip6;
        if (rp->ai_family == AF_INET) {
            //printf("AFNET Length: %u\n", rp->ai_addrlen);
            ip4 = (struct sockaddr_in*)rp->ai_addr;
            port4 =  ((struct sockaddr_in*)rp->ai_addr)->sin_port;
            addr = &(ip4->sin_addr);
            ipver = "ipv4";
        } else {  // AF_INET6
            //printf("AF_INET6 Length: %u \n", rp->ai_addrlen);
            ip6 = (struct sockaddr_in6*)rp->ai_addr;
            port6 =  ((struct sockaddr_in6*)rp->ai_addr)->sin6_port;
            addr = &(ip6->sin6_addr);
            ipver = "ipv6";
        }

        inet_ntop(rp->ai_family, addr, ipstr, sizeof ipstr);
        printf("Ip Version: %s\nIP: %s \nCanon Name: %s\n", ipver, ipstr, rp->ai_canonname );
        printf("Port: %hu %hu \n\n", ntohs(port4), ntohs(port6));
    }

    return result;
/* inet_ntop - binary to string IP translation 
    char ip4[INET_ADDRSTRLEN];  // INET6_ADDRSTRLEN for ip6
    struct sockaddr_in sa; 
    sa.sin_addr.s_addr = 3580759050; // "10.12.110.213" from section below 

    inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);
    printf("IPv4 address is %s:", ip4 );
    */
/* inet_pton - ip string to binary

    //struct sockaddr_in* sa = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in )); 
    struct sockaddr_in sa;
    struct sockaddr_in6 sa6; 
    //memset(&sa, 0, sizeof (struct sockaddr_in));

    inet_pton(AF_INET, "10.12.110.213", &(sa.sin_addr)); // 3580759050 from above
    inet_pton(AF_INET6, "ffff:eeee:ffff::", &(sa6.sin6_addr));
    printf("-- %u\n", sa.sin_addr.s_addr);
    for (uint8_t x=0; x<16; x++) {
        printf("%u", sa6.sin6_addr.s6_addr[x]);
    }
    
*/
}
/* socket reference data structures
struct sockaddr {                   // Common address structure to be cast into
    unsigned short   sa_family; 2
    char            sa_data[14];    // address+port - not enough for IPv6 (16 bytes)
                                    // the number 14 is variable based on sa_family
}  

struct sockaddr_in {                 // ipv4
    short int          sin_family;   // Address family, AF_INET
    unsigned short int sin_port;     // Port number
    struct in_addr     sin_addr;     // Internet address
    unsigned char      sin_zero[8];  // Same size as struct sockaddr
}           

struct in_addr {
    uint32_t s_addr;                 // 4 bytes ipv4 address (example: 10.12.32.xx)
}

struct sockaddr_in6 {}               // ipv6 (almost same as above)

struct in6_addr {
    uint8_t s6_addr[16];             // 16 bytes ipv6 address (example: ffee:fdee:efff:11e2::xxxx)
}

struct sockaddr_storage {            // can store both Ipv4 and Ipv6 - with padding
    unsigned char ss_family; 
    .. some padding; 
}  

*/