#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// int64_t recur_sum(int64_t n) {
//     if (n <= 0)
//         return 0;
//     else
//         return n + recur_sum(n-1);
// }

struct person {
    char* name1;       // was 
    //char name[20];
    bool has_magic;
};

int main(int argc, char** argv) {

    printf("Size %zu", sizeof(struct person));


    // int64_t n = 10000000;
    // if (argc > 1)
    //     printf("\n---\n");
    //     n = atoll("10000000");
    //     printf("%lld==\n", n);
    // printf("%lld\n", recur_sum(n));
}