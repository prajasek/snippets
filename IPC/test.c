#include <stdio.h>

int main() {
    char name[50]; 
    for (int i=0; i<100; i++) {
        sprintf(name, "SHM_%d", i);
        printf("Name= %s\n", name);
    }
}