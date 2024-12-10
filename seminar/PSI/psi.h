#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define SYMBOL 0
#define INTEGER 1
#define BOOL 2 

// Implement bracket equality check 
// Check if expression is valid


typedef struct Data {
    int type; 
    void* value;
} Data;

typedef struct Node {
    struct Node* left; 
    struct Node* right; 
    struct Data* data; 
} Node;

int add(Node* left, Node* right);
int subtract(Node* left, Node* right);
int divide(Node* left, Node* right);
int multiply(Node* left, Node* right);

int evaluate(Node*);
void add_to_tree(Node* , Node* );
Node* parse(char* );
Node* create_node(char* , int , int );
void lisp(char* ); 