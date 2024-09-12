#include "stdio.h"
#include <stdint.h>
#include <string.h>


int main(int argc, char** argv) {
    unsigned char word[128];

    uint8_t code = 97;      // lower-case 97-122
    uint8_t count = 0; 
    unsigned char* c = NULL;
    while (code < 123) {
        count=0;
        for (uint8_t i=1; i<argc; i++) {
         //   printf("i = %d\n", i);
            unsigned char* word=argv[i];
            for (c=word ; *c!=0; c++) {
                if (*c==code) {
                    count++;
               //     printf("yes %c - %hu\n", *c, count);

                }
            }
        }
       if (count) printf(" %c %d\n", code-32, count);
        code++;
    }
}