#include <mqueue.h>

#define QNAME "/queue1"
#define RW_OWNER S_IRWXU
#define RW_GROUP S_IRWXG

typedef struct message {
    char message[100]; 
    char name[100];
} MSG;

void push_msg(mqd_t , char* , char* );

void push_end_signal(mqd_t );