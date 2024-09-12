#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

    char* str = "Hello\\There\\My\\Friend\\";
    char* tokens[10];
    int counter_tokens =0;
    char token[50]; 
    memset(token, 0, 50);
    int counter=0;
    char DELIMITER = '\\';

    for (char* s=str;; s++){
        printf("char : %c\n", *s);
        if (*s == DELIMITER){
            char* buff= (char*) malloc(10*sizeof(char));
            memset(buff, 0, 10);
            tokens[counter_tokens] = buff;
            strcpy(tokens[counter_tokens], token); 
            //printf("string: %s\n", tokens[counter_tokens]);
            counter_tokens++;
            memset(token, 0, 50);
             printf("token : %s \n", token);
            counter=0;
            //free(buff);
        }
        else if (*s == '\0'){
    
            if (token[0]!='\0') 
            {   
                tokens[counter_tokens] = token; 
                printf("string: %s\n", tokens[counter_tokens]);
            }
            tokens[++counter_tokens] = NULL;
            break;
        } else {
            token[counter++]=*s;
            printf("token : %s \n", token);
        }
        
    }

    for (int i=0;; i++){
        if (tokens[i]==NULL) break;
        printf("Token :%d %s\n", i, tokens[i]);

    }



}