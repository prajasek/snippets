#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char* path = "/courses/ud923/filecorpus/paraglider.jpg";
    char req[100+20] = "GETFILE GET ";
    strcat(req, path);
    strcat(req, "\r\n\r\n");
    printf("Request header: %s", req);
  
  
  
  
  
  
  
  
    // unsigned int port = 122132;
    // char output[10]="AVc123456";

    // // sprintf(output, "%u", port);
    // printf("PORT %s: ", output);
}   