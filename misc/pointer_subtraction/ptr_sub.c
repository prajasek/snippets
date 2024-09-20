#include <stdio.h>
#include <string.h>

int main() {

    char* a = "Hello World";
    char* b = &a[7];

    size_t diff= b - a; 
    printf("Diff: %zu\n", diff);
    printf("Strings (%s) (%s)\n", a, b);

    char c[10] = {0};
    memcpy(c, a, 7);
    printf("Strings (%s)", c);


}