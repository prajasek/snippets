#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

#include "mq.h"

int msg_len =0; 

void push_msg(mqd_t mqdes, char* ID, char* message) {
    MSG m;
    msg_len = msg_len + (int)sizeof(m);
    printf("Size of total messages = %d\n", msg_len);
    memset(&m, 0, sizeof(MSG));
    memcpy(&(m.message), message, strlen(message)); 
    memcpy(&(m.name), ID, strlen(ID)); 
    
    const char* msg = (const char*) &m;
    size_t len = sizeof(MSG);

    mq_send(mqdes, msg, len, 10); 
    printf("Message %s with ID %s send\n", message, ID);
}


void push_end_signal(mqd_t mqdes) {
    MSG m;
    memset(&m, 0, sizeof(MSG));
    memcpy(&(m.message), "----EOF----", 11); 
    memcpy(&(m.name), "----FOE----", 11); 
    
    const char* msg = (const char*) &m;
    size_t len = sizeof(MSG);

    mq_send(mqdes, msg, len, 10); 
    printf("EOF sent.\n");
}


int main() {
    mqd_t mqdes; 
    int flags = O_RDWR | O_CREAT | O_EXCL;
    struct mq_attr attr;

    mqdes = mq_open(QNAME, O_RDWR | O_CREAT | O_EXCL , 0600, NULL);

    if (mqdes == -1) {
        printf("Queue already exists.\n");
        mqdes = mq_open(QNAME, O_RDWR, 0600, NULL);
        printf("FD: %d\n", mqdes);
    }

    char id[50];
    char content[100];
    for (int i=0; i<6; i++) {
        /* SharedMemory ID send through message queue */
        sprintf(id, "SHM_%d", i);
        /* Message content */
        sprintf(content, "MSG_%d_END", i);
        push_msg(mqdes, id, content); 
    }
    push_end_signal(mqdes);    
    mq_close(mqdes);
}


// Working Example:
// -------------------
// char* message = "Hello There\n";
// size_t len = strlen(message);
// len = len+1; 
// for (int i=0; i< 10; i++) {
//     mq_send(mqdes, message, len, i);
// }