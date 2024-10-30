#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

#define QNAME "/queue1"
#define RW_OWNER S_IRWXU
#define RW_GROUP S_IRWXG

typedef struct message {
    char message[100]; 
    char name[100];
} MSG;

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
    MSG m;
    memset(&m, 0, sizeof(MSG));
    memcpy(&(m.message), "1234567890 MESSAGE", 18); 
    memcpy(&(m.name), "SHM01", 5); 

    const char* msg = (const char*) &m;
    size_t len = sizeof(MSG);

    mq_send(mqdes, msg, len, 10); 

    // Working Example:
    // -------------------
    // char* message = "Hello There\n";
    // size_t len = strlen(message);
    // len = len+1; 
    // for (int i=0; i< 10; i++) {
    //     mq_send(mqdes, message, len, i);
    // }
    
    
    mq_close(mqdes);

}