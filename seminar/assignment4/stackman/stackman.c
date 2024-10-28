#include "stackman.h"

/* Globals */
uint16_t stack[STACK_SIZE] = {0};
uint16_t top               = 0;
uint16_t n_elements        = 0; 

/* Displays all elements of stack */
void print_stack(char op) {
    printf("----------------------------------\n");
    if (op == '1') {
        printf("Interpretation Complete.\n");
        printf("\nStack:\n[ ");
    } else {
        printf("N=%d, TOP=%d, OPERATION= %c\n[ ", n_elements, top, op);
    }
    for (int i=0; i<=top; i++) {
        printf("%d, ", stack[i]);
    }
    printf("] \n");
    printf("----------------------------------\n");
}

/* Rotates the stack right by one place */
void rotate_stack_right(int n) {
    printf("n = %d\n", n);
    uint8_t temp = stack[top];
    for (int i=top-1; i>=top-n+1; i--) { 
        stack[i+1] = stack[i];
    }
    stack[top-n+1] = temp;
}

/* Rotates the stack left by one place */
void rotate_stack_left(int n) {
    uint8_t temp = stack[top-n+1];
    for (int i=top-n+1; i<top; i++) { 
        stack[i] = stack[i+1];
    }
    stack[top] = temp;
}

/* Check stack against the error code and exit if error */
void check_stack(int op, uint8_t code) {
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
                printf("Number of elements = %d %d\n", n_elements, STACK_SIZE);
                if (n_elements >= 65536) {
                    printf("Error at OP: %c. Stack Overflow. Exiting.\n", DUP);
                    exit(code);
                }
                break;
            }
        case ROTR:
        case ROTL:
            printf("Error at ROTx. Not enough elements. Exiting. \n");
            exit(code);
        case LPAR: 
        case RPAR: 
        case 0:
            printf("Syntax Error. \n");
            exit(code);
    }
}

/* Evaluate the loop expression. Moves the expression pointer after the loop. 
 * NOTE: Honestly, we shouldnt have to return the char* since we are passing 
 * in the location of the pointer itself to take ownership, but I am running 
 * out of time to figure why it doesnt update the global expression pointer. 
 * Returning adjusted expression pointer works as a band-aid fix, but need 
 * to solve this. */
char* loop_expression(char** expr) {
    char* expression = *expr; 

    /* Move pointer after the left paranthesis*/
    if (*expression == LPAR) expression = expression + 1;
    int len = strlen(expression);
    printf("Expression: %s\n", expression);

    /* Loop expression aggregate */
    char* loop_expr = (char*) malloc (len*sizeof(char));
    memset(loop_expr, 0, len);
    
    char c; 
    int i=0; 
    while (*expression != EOF || *expression != '\0') {
        c = *(expression);

        /* Handles inner loop */
        if (c == LPAR) {
            /* Recursive call to function for handling inner loop.
             * Returns pointer after the loop ')'   */
            expression = loop_expression(&expression);

            /* Dont add the ')' to expression aggregate */
            continue;
        }
        loop_expr[i++] = c; 
        expression++;
        
        /* Right parenthesis found. We add the right parenthesis as a check
         * to know we exited the loop for the correct reason. */
        if (c == RPAR) {
            if (*(expression) == DROP ) {
                printf("Found %c\n", *(expression));
                break;
            }
            else check_stack(0, SYN_ERROR);
        }
    }
    
    /* If EOF or end of expression */
    if (loop_expr[i-1] != RPAR) {
        check_stack(LPAR, SYN_ERROR);
    }
    assert(loop_expr[i-1] == RPAR);

    /* Remove ')' from the loop expression */
    loop_expr[i-1] = '\0'; 

    /* Since inner loop tends to make the TOS=0, we want to evaluate */
    do {
        printf("Evaluating ...\n");
        evaluate(&loop_expr);
    }
    while (stack[top] && *expression != EOF && *expression != '\0');
    handle_EO_loop();
    expression++;
    printf("Exiting loop.\n\n");
    printf("=============================================================================================\n");
    return expression;
}


void handle_EO_loop() {
    check_stack(DROP, STACK_UFLOW);
    top--;
    n_elements--;
    print_stack(DROP);
}

/* Evaluate expression and manipulate stack */
void evaluate(char** expr) {
    char* expression = *expr;
    int i = 0 ; 
    char c; 
    int temp; 
    printf("\n*********************************************\n");
    printf("Entering Evaluation. Expression to evaluate: %s\n", expression);
    while ((c = expression[i])!=EOF && (c = expression[i++])!='\0') {
        switch (c) {
            case ZERO:
                if (!n_elements) {
                    stack[top] = 0;
                    n_elements++; 
                    print_stack(ZERO);
                    break;
                }
                stack[++top] = 0; 
                n_elements++;
                print_stack(ZERO);
                break;
            case ADD_ONE: 
                check_stack(ADD_ONE, STACK_UFLOW); 
                stack[top]++;
                print_stack(ADD_ONE);
                break;
            case DROP: 
                check_stack(DROP, STACK_UFLOW);
                top--;
                n_elements--;
                print_stack(DROP);
                break;
            case DUP: 
                check_stack(DUP, STACK_UFLOW);
                check_stack(DUP, STACK_OFLOW);
                stack[++top] = stack[top]; 
                n_elements++;
                print_stack(DUP);
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
                print_stack(TEST);
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
                print_stack(ROTR);
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
                print_stack(ROTL);
                break;     
            case LPAR: 
                expression = expression+i;
                expression = loop_expression(&expression);
                printf("Expression returned = %s\n", expression);
                i=0;
                break;
            case SPACE:
            case '\0':
                break;
            default:
                printf("Invalid character: %c\n", c);
                check_stack(INVALID, SYN_ERROR);
                break;
        }
    }
}

/* Read file and return contents (expression)*/
char* read_file(FILE* file) {
    char* expression = (char*)malloc(STACK_SIZE*sizeof(char));
    char c; 
    memset(expression, 0, STACK_SIZE);
    int i=0; 

    /* Saves the EOF character as well. Used for iteration. */
    while (!feof(file)) {
        expression[i++] = fgetc(file);
    }
    return expression; 
}

int main(int argc, char* argv[]) {
    char* filename = "test";
    printf("File = %s\n", filename);
    FILE* file = fopen(filename, "r");
    char* main_expression = read_file(file);
    evaluate(&main_expression);
    /* Signal End of Interpretation */
    print_stack('1');
}
