#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <stdlib.h>
#include <sys/stat.h>

#define QNAME "/queue1"
#define RW_OWNER S_IRWXU
#define RW_GROUP S_IRWXG

typedef struct message {
    char message[100];  
    char name[100];
} MSG;

void printer(int i) {
    printf("%d", i);
}

int main() {

    mqd_t mqdes; 
    int flags = O_RDWR | O_CREAT | O_EXCL;
    struct mq_attr attr;

    mqdes = mq_open(QNAME, O_RDONLY );

    int f = mq_getattr(mqdes, &attr);

    if (f==-1) printf("Error at f\n");

    char* msg = calloc (attr.mq_msgsize, 1);

    int priority = 0; 

    while (1) {
        if (mq_receive (mqdes, msg, attr.mq_msgsize, &priority) == -1) {
            printf("Something failed.\n");
            break;
        }
        else {
            MSG* m = (MSG*)msg; 
            printf("Message: %s\n", m->message);
            printf("Name: %s\n", m->name);
            printf("Priority: %d\n", priority);

            if (strcmp(m->message, "----EOF----") ==0 && strcmp(m->name, "----FOE----") == 0) {
                printf("End of message reached. \n");
                break;
            }
        }
    }

    printf("All messages retrieved.\n");
    mq_close(mqdes);
    mq_unlink(QNAME);

    for (int i=0; i<1000; i++) {
        printer(i);
    }
}