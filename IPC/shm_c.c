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

    int shm_fd = shm_open(NAME, O_RDWR, 0600);

    if (shm_fd < 0) {
        if (errno == ENOENT) {
            printf("Error: %d. Shared memory object does not exist. \n", errno);
            exit(1);
        }
    }

    char* data = (char *) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    printf("Data : \n %s \n", data); 

    close(shm_fd);
    shm_unlink(NAME);
}

/* Create N shared memory of size SIZE in the proxy. 
 * Create 2 semaphore for each memory segment (N*2 semaphores).
 * Create a message queue in the Proxy.
 * There is one single message queue between Proxy thread and Boss worker in Cache, which we are free to implement. 
 *          - This is equivalent to receiving a GETFILE request in MT approach. 
 *          - Create a cache thread using the shared memory name as parameter
 * PROXY steque - Shared Memory Pool
 *                  - contains the shm_name
 * The proxy server thread picks a shared memory segment from the pool with names as ID. 
 *          - Pack a struct S with:
 *                  - char* req - GETFILE request
 *                  - char* shm_name - shared memory name
 *                  - char* sem_proxy - name of proxy semaphore 
 *                  - char* sem_cache - name of cache semaphore
 *          - Write to a message queue with struct S. 
 *          - Proxy waits by the sem_cache to know when data is written in the shared memory. 
 *          - Once data is read, it signals sem_proxy to ask cache to write more data. 
 *          - Once data is fully read, it closes the shared_memory fd shm_close(), and the sem_clos ().
 *          - Clear the S->req to 0. Add the struct S back to the queue. 
 *          - Another thread can pick up the shared memory from the pool. 
 * 
 * 
 * CACHE steque - message from message queue
 * Each thread picks up a message from the message queue. 
 * Parse the message queue to get S->req, S->shm_name, S->semaphores
 * Get data from the cache, write header, and send data and sem_post. Once done, write some custom EOF token. 
 * Close - shm_close and sem_close. 
 * Pick up another message from the steque.
 * 
 * 
 *                               Thread 1  ---                                                                               Thread 1
 *                 steque      /                \                                                       steque             / 
 *    PROXY -- [SH Mem Pool] --  Thread 2  ---   ------[MESSAGE QUEUE]------- CACHE BOSS WORKER --> [ Request Packet ] ----  Thread 2 
 *                             \                /                                                                          \  
 *                               Thread 3  ---                                                                               Thread 3
 *  
 */ 