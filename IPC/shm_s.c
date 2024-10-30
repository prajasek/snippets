#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define NAME "/shm_01"
#define SIZE 1000

int main() {
    int shmfd = shm_open(NAME, O_CREAT | O_EXCL | O_RDWR, 0600); 
    if (shmfd < 0) {
        printf("Error.\n");
        shmfd = shm_open(NAME, O_RDWR, 0600); 
        char* m = "Different message --EOF";
        char *data = (char *) mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
        strncpy(data, m, SIZE);
        close(shmfd);
        exit(1);
    }

    char* m = "Shared message data --EOF__EOF";

    ftruncate(shmfd, SIZE);
    char *data = (char *) mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    strncpy(data, m, SIZE);

    munmap(data, SIZE);
    close(shmfd);
    return 0; 
}