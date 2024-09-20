#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char input[] = "GETFILE FILENAME C:\\get \r\n\\n";
    char* p = strstr(input, "\r\n\r\n");
    if (p!=NULL) printf("FOUND: %s\n", p);
    
    printf("%d", atoi("11111111111111111111111111111111111"));
}   