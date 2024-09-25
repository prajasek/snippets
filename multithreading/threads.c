#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int counter =0 ; 
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; 



void* worker(void* path){
    char* p = (char*) path;
    printf("Path Passed: %s from %ld\n", p, (pthread_self()/100000)%100);
    //printf("\nCounter START: %d -- %ld\n", counter,  (pthread_self()/100000)%100);
    //printf("\nEntering CRITICAL SECTION %d -- %ld\n", counter,  (pthread_self()/100000)%100);
    pthread_mutex_lock(&mut);
    while (counter < 10) {

        printf("Counter %d\n", counter);
        counter++;
    
    }
pthread_mutex_unlock(&mut);

    printf("DONE: %ld\n", (pthread_self()/100000)%100);
}

void main(){
    pthread_t threads[10];
    memset(threads, 0, sizeof(threads));

    for (int i=0; i<10; i++){
        char path[10];
        sprintf(path, "thr_msg=%d", i);
        int x =pthread_create(&threads[i], NULL, worker, (void*) path);
        printf(">>>>>>>>>>>>>>>>>>> Created %ld\n", (threads[i]/100000)%100);
    }
    
    for (int i=0; i<10; i++){
        printf("Thread value : %ld\n", (threads[i]/100000)%100);
    }
    printf("Condition = %d\n", counter);    
    for (int i=0; i<10; i++){
        pthread_join(threads[i], NULL);
    }
    printf("COUNTER: %d\n", counter);
}   