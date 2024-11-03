#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pthread.h>
#include "mq.h"

#define SEM_NAME "/bin-sem"

typedef struct pack {
    mqd_t mqdes; 
    sem_t* sem;
} T_INFO;


void* sender(void* arg) {
    T_INFO* t = (T_INFO*)arg;
    sem_wait(t->sem);
    printf("Pthread critical --------------------%ld\n", pthread_self());
    printf("%d", t->mqdes);
    push_msg(t->mqdes, "HEHE", "MESSAGE THREAD");
    sem_post(t->sem);
}


int main() {
    T_INFO* info = (T_INFO*) malloc(sizeof(T_INFO)); 
    printf("my pid = %d", getpid());
    pthread_t t1, t2; 
    mqd_t mqdes; 
    int flags = O_RDWR | O_CREAT | O_EXCL;
    struct mq_attr attr;

    mqdes = mq_open(QNAME, O_RDWR | O_CREAT | O_EXCL , 0600, NULL);

    if (mqdes == -1) {
        printf("Queue already exists.\n");
        mqdes = mq_open(QNAME, O_RDWR, 0600, NULL);
        printf("FD: %d\n", mqdes);
    }

   

    sem_t* sem = sem_open(SEM_NAME, O_CREAT | O_EXCL |O_RDWR, 0600, 1);
    if(sem == SEM_FAILED) {
        printf("Named semaphore exists\n");
        sem = sem_open(SEM_NAME, O_RDWR);
    }
    printf("info\n");
    info->mqdes = mqdes;
    info->sem = sem;
    printf("Packed\n");

    pthread_create(&t1, NULL, sender, (void*)info);
    pthread_create(&t2, NULL, sender, (void*)info);

    printf("Thread created");
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    push_end_signal(mqdes);
    
    free(info);
    mq_close(mqdes);
    sem_close(sem);
    sem_unlink(SEM_NAME);

}