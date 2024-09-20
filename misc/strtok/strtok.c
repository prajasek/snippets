#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char* parse_header(char*);

int main() {
    char input[] = "GETFILE ER1ROR\r\n\r\n";
    char* s= parse_header(input);
    assert(strcmp(s, "ERROR")==0);
    size_t d = atoll("2");  //18446744073709551615
    printf("atoi %zu %zu\n" , d, sizeof(unsigned long));
    //assert(d==1);
    printf("Ending\n");

}




char* parse_header( char* header_buffer) {
    char* ptr;
    size_t size = strlen(header_buffer);
    char TMP[size];
    memset(TMP, 0, size);
    strcpy(TMP, header_buffer);
    ptr = strtok(TMP, " ");    // GETFILE
    ptr = strtok(NULL, "\r");
    char* status; 
    if (strstr(ptr, " ")!=NULL) {
        printf("yes\n");
        status = strtok(ptr, " ");
        printf("STATUS : <%s>\n", ptr);
        ptr = strtok(NULL, "\r");
        printf("LEN: <%s>\n", ptr);
    } else {
        status = ptr; 
        printf("STATUS: <%s>\n", ptr);
    }
    return status;

}