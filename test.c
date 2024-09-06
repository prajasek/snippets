#include <stdio.h> 

int main() {

    typedef struct BIG {
        int x; 
        int y; 
        int z; 
    } BIG;

    typedef struct SMALL {
        int x; 
    } SMALL ; 

    SMALL *s, so; s = &so;

    s->x= 100;

    printf("%d\n", s-> x)    ;

    BIG *bigp = (BIG *)s;
    bigp->y = 10120; 
    bigp->z = 200; 

    printf("%d, %d -- ", bigp->y, bigp->z);

    printf("%d : ", s->x);
}