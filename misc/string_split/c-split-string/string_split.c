#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOKENS 100
#define WORDSIZE 50

/* Split string based on the delimiter provide 
 * as command line arguments */
int main(int argc, char* argv[]) {
    char* DELIMITER = " ";
    char* str = "This is a test string. Please enter string and delimiter in the command line.";
    if (argc==3) {
        str = argv[1];
        DELIMITER = argv[2]; 
    } 
    
    printf("\nString: %s\n", str);
    printf("Delimiter: %s\n\n", DELIMITER);

    /* @counter - index of each character in a token/word
     * @counter_tokens - index of each token/word in list of tokens/words 
     * @token  - single token/word 
     * @tokens - list of tokens/words being collected
     */
    int counter=0, counter_tokens =0;
    char* tokens[TOKENS];
    char token[WORDSIZE]; 
    memset(tokens, 0, TOKENS);
    memset(token, '\0', WORDSIZE);

    /* Split tokens/words based on DELIMITER into each @token and store them into @tokens.
     * This ignores empty string between consecutive delimiters placed next to each other, 
     * and between delimiter and end of string
     */
    for (char* s=str;; s++){
        if (*s == *DELIMITER || *s=='\0') {
            /* empty string between delimiters OR delimiter at beginning or end. */
            if (token[0]!='\0') {               
                tokens[counter_tokens] = (char*) malloc(WORDSIZE*sizeof(char));
                strcpy(tokens[counter_tokens++], token);
            }

            /* reached end of string */
            if (*s=='\0') {                    
                tokens[counter_tokens] = NULL;
                break;
            }
            memset(token, '\0', WORDSIZE);
            counter=0;
        } 
        else {
            /* keep adding characters to form a token/word */
            token[counter++]=*s;
        }
    }

    /* Find last token/word */
    char* last_token;
    int i=0;
    while(tokens[i]!=NULL) {
        last_token = tokens[i++];
    }

    /* Display all tokens/words */
    printf("Number of words: %d\n", counter_tokens);
    printf("Words:           [ ");
    for (int i=0;; i++){
        if (tokens[i]==NULL) {
            printf(" ]\n");
            break;
        }
        /* Just for display purposes: 
         * No comma at the start before elements */
        if (i) printf(", ");      
        printf("'%s'", tokens[i]);
    }
    printf("Last token:      %s\n\n", last_token);

    /* Another way of iterating:
     * ---------------------------
     * char** word = tokens; 
     * while (*word != NULL) {
     *   printf("TOKEN :%s\n", *word);
     *   word++;
     * } 
     */

    /* Done. Clean-up */
    for (int index=0; index<counter_tokens; index++ ) {
        free(tokens[index]);
    }

}