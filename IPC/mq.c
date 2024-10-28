#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

#define QNAME "/queue1"
#define RW_OWNER S_IRWXU
#define RW_GROUP S_IRWXG

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

    char* message = "Hello There\n";
    size_t len = strlen(message);
    len = len+1;

    for (int i=0; i< 10; i++) {
        mq_send(mqdes, message, len, i);
    }
    
    
    mq_close(mqdes);

}