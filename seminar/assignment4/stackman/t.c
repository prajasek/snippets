#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

int main(int argc, char* argv[]) {
    char* filename = "test";
    printf("File = %s\n", filename);
    FILE* file = fopen(filename, "r");
    unsigned int x= -2;
    
    while (!feof(file)) {
        char c = fgetc(file);
        printf("-- %d\n", (int)c);
    }
    printf("****%u\n", x);
}