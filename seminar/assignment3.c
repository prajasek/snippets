#include "stdio.h"
#include <stdint.h>
#include <string.h>


int main(uint8_t argc, char** argv) {
    unsigned char word[128];            // we know each word length < 128
    uint8_t code = 97;                  // lower-case 97-122
    uint8_t count = 0; 
    unsigned char* c = NULL;
    while (code < 123) {
        count=0;
        for (uint8_t i=1; i<argc; i++) {
            strcpy(word, argv[i]);       // safe assuming each word length < 128
            for (c=word ; *c!='\0'; c++) { 
                if (*c==code) {
                    count++;
                }
            }
        }
        if (count) printf("%c %d\n", code-32, count);
        code++;
    }
}