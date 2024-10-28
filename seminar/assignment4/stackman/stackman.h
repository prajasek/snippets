#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

/* Operations */
#define ZERO    '0'
#define ADD_ONE '+'
#define DROP    '_'
#define DUP     '~'
#define TEST    '?'
#define ROTR    '>'
#define ROTL    '<'
#define LPAR    '('
#define RPAR    ')'
#define SPACE   ' '
#define EMPTY   ''


/* Error Codes */
#define STACK_UFLOW 1
#define STACK_OFLOW 2
#define SYN_ERROR   3 
#define INVALID    -1

/* Globals */
#define STACK_SIZE 65536

/* Functions */
void print_stack(char);
void rotate_stack_right(int); 
void check_stack(int, uint8_t);
char* loop_expression(char**);
char* read_file(FILE*) ;
void evaluate(char**);
void handle_EO_loop();