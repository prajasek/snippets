#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <stdlib.h>
#include <sys/stat.h>

#define QNAME "/queue1"
#define RW_OWNER S_IRWXU
#define RW_GROUP S_IRWXG

int main() {

    mqd_t mqdes; 
    int flags = O_RDWR | O_CREAT | O_EXCL;
    struct mq_attr attr;

    mqdes = mq_open(QNAME, O_RDONLY );

    int f = mq_getattr(mqdes, &attr);

    if (f==-1) printf("Error at f\n");

    char* msg = calloc (attr.mq_msgsize, 1);

    int priority = 0; 

    if (mq_receive (mqdes, msg, attr.mq_msgsize, &priority) == -1) {
        printf("Something failed.\n");
    }
    else {
        printf("Message: %s\n", msg);
        printf("Priority: %d\n", priority);
    }


}