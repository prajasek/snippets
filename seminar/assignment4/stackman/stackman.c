#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Operations */
#define ZERO    '0'
#define ADD_ONE '+'
#define DROP    '_'
#define DUP     '~'
#define TEST    '?'
#define ROTR    '>'
#define ROTL    '<'
#define EMPTY   ''
#define LPAR    '('
#define RPAR    ')'

/* Exit Codes */
#define STACK_UFLOW 1
#define STACK_OFLOW 2
#define SYN_ERROR   3 

/* Globals */
#define STACK_SIZE 65536
uint16_t stack[STACK_SIZE] = {0};
uint16_t top               = 0;
uint16_t n_elements        = 0; 

/* Displays all elements of stack */
void print_stack() {
    printf("-------------------------\n");
    printf("n=%d top=%d   [ ", n_elements, top);
    for (int i=0; i<=top; i++) {
        printf("%d, ", stack[i]);
    }
    printf(" ] \n");
    printf("-------------------------\n");
}

void rotate_stack_right(int n) {
    printf("n = %d\n", n);
    uint8_t temp = stack[top];
    for (int i=top-1; i>=top-n+1; i--) { 
        stack[i+1] = stack[i];
    }
    stack[top-n+1] = temp;
}

void rotate_stack_left(int n) {
    uint8_t temp = stack[top-n+1];
    for (int i=top-n+1; i<top; i++) { 
        stack[i] = stack[i+1];
    }
    stack[top] = temp;
}

/**/
void check_stack(uint8_t op, uint8_t code) {
    switch (op) {
        case ZERO: 
            // overflow
            break;
        case ADD_ONE: 
        case DROP: 
        case TEST:
            if (!n_elements) {
                printf("Error. Stack Underflow. Exiting.\n");
                exit(code);
            }
            break;
        case DUP:
            if (code == STACK_UFLOW) {
                if (!n_elements) {
                    printf("Error at OP: %c. Stack Underflow. Exiting.\n", DUP);
                    exit(code);
                }
                break;
            }
            if (code == STACK_OFLOW) {
                printf("Error at OP: %c. Stack Overflow. Exiting.\n", DUP);
                if (n_elements >= STACK_SIZE) 
                    exit(code);
                break;
            }
        case ROTR:
        case ROTL:
            printf("Error at ROTx. Not enough elements. Exiting. \n");
            exit(code);
            break;
    }
}

int loop_expression(file) {
    char expression[STACK_SIZE];
    char c; 
    memset(expression, 0, STACK_SIZE);
    for (int i=0; i<STACK_SIZE; i++) {
        c = fgetc(file);
        if (c == EOF) break;
        expression[i] = c; 
        if (c == RPAR) break; 
    }
    if (expression[0]=='\0') return -1;
    return 1; 
}


int main(int argc, char* argv[]) {
    char* filename = argv[1];
    FILE* file = fopen(filename, "r");
    char c; 
    int temp; 
    while ((c = fgetc(file))!=EOF) {
        switch (c) {
            case ZERO:
                if (!n_elements) {
                    stack[top] = 0;
                    n_elements++; 
                    print_stack();
                    break;
                }
                stack[++top] = 0; 
                n_elements++;
                print_stack();
                break;
            case ADD_ONE: 
                check_stack(ADD_ONE, STACK_UFLOW); 
                stack[top]++;
                print_stack();
                break;
            case DROP: 
                check_stack(DROP, STACK_UFLOW);
                top--;
                n_elements--;
                print_stack();
                break;
            case DUP: 
                check_stack(DUP, STACK_UFLOW);
                check_stack(DUP, STACK_OFLOW);
                stack[++top] = stack[top]; 
                n_elements++;
                print_stack();
                break;
            case TEST:
                check_stack(TEST, STACK_UFLOW);
                if (stack[top]) {
                    stack[top]--; 
                    stack[++top] = 1; 
                } else {
                    stack[++top] = 0; 
                }
                n_elements++;
                print_stack();
                break;
            case ROTR:
                temp = stack[top--];
                n_elements--; 
                if (temp >= 2) {
                    if (n_elements < temp) {
                        check_stack(ROTR, STACK_UFLOW);
                    }
                    rotate_stack_right(temp);
                }
                print_stack();
                break;
            case ROTL:
                temp = stack[top--];
                n_elements--; 
                if (temp >= 2) {
                    if (n_elements < temp) {
                        check_stack(ROTL, STACK_UFLOW);
                    }
                    rotate_stack_left(temp);
                }
                print_stack();
                break;     
            case LPAR: 
                loop_expression(file);

        }
    }



}
