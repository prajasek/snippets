#include "psi.h"

int add(Node* left, Node* right) {
    int v = evaluate(left) + evaluate(right);
    return v; 
}

int subtract(Node* left, Node* right) {
    int v = evaluate(left) - evaluate(right);
    return v; 
}

int divide(Node* left, Node* right) {
    int v = evaluate(left) / evaluate(right);
    return v; 
}

int multiply(Node* left, Node* right) {
    int v = evaluate(left) * evaluate(right);
    return v; 
}

int evaluate(Node* tree) {
   // printf("Evaluating...%p\n", tree);

    int type = tree->data->type; 
    if (type == SYMBOL) {
        char* value = (char*) (tree->data->value);
       // printf("Value :%s\n", value);

        if (strcmp(value, "+") ==0) {
        //    printf("Addition\n");
            return add(tree->left, tree->right);
        }

        if (strcmp(value, "-") ==0) {
        //    printf("Addition\n");
            return subtract(tree->left, tree->right);
        }

        
        if (strcmp(value, "/") ==0) {
        //    printf("Addition\n");
            return divide(tree->left, tree->right);
        }

        
        if (strcmp(value, "*") ==0) {
       //     printf("Addition\n");
            return multiply(tree->left, tree->right);
        }
    } else if (type == INTEGER) {
        int value = *(int*)(tree->data->value);
        return value;
    } else {
        return -1;
    }
}

void add_to_tree(Node* tree, Node* node) {
 //   printf("Pointers Add to Tree: %p %p\n", tree, node);
    if (tree->data == NULL) {
      //  printf("Empty\n");
        Data* d = (Data*) malloc (sizeof (Data));
        tree->data = d; 
        tree->data->type = node->data->type;
        tree->data->value = node->data->value;
        return;
    }
  //  printf("Non Empty \n");
    if (tree->left == NULL) {
        tree->left = node; 
        return;
    } 

    if (tree->right == NULL) {
        tree->right = node; 

        return; 
    }
}

Node* create_node(char* expression, int start, int end) {
  //  printf("1--\n");

    Node* node = (Node*) malloc(sizeof (Node));
    Data* d = (Data*) malloc (sizeof (Data));

    memset(node, 0, sizeof(Node));
    memset(d, 0, sizeof(Data));

  //  printf("2--\n");

    int size = end-start+1;
    char* buff = (char*) malloc (size);
 //   printf("Size = %d\n", size);
    memset(buff, 0, size);
    memcpy(buff, &expression[start], size-1);
 //   printf("Buff =<%s>\n" , buff);
    
    int buff_len = strlen(buff);

    if (buff[0] == '(' &&  buff[buff_len-1]==')') {
        return parse(buff);
    }
  //  printf("7--\n");

    if (buff[0] == '+' || buff[0] == '-' || buff[0] == '/' || buff[0] == '*') {
  //      printf("4--\n");
        d->type = SYMBOL; 
        d->value = buff;
        node->data = (void*)d; 
  //      printf("5--\n");
  //      printf("-> %s\n" , node->data->value);
  //      printf("CreateNode Pointer Returned: %p\n", node);

        return node;
    }
    d->type = INTEGER; 
    int* v = (int*) malloc (sizeof(int));
    *v = atoi(buff);
    d->value = (void*)v; 
    node->data = d; 
  //  printf("DATA: v=%d and type=%d\n", *(int*)(node->data->value), node->data->type);
  //  printf("CreateNode Pointer Returned: %p\n", node);

    return node; 
}

Node* parse(char* expression) {
    printf("Parsing...%s\n", expression);

    Node* tree = (Node*) malloc (sizeof (Node));
 //   printf("Pointers TREE: %p\n", tree);

    tree->left = tree->right = tree->data = NULL; 

    int len= strlen(expression);
  //  printf("Len = %d\n", len);
    int count= 0;
    int start = 1;
    int end = 0;  
    for (int i=1; i<len-1; i++) {
        if (expression[i] == '(') {
    //        printf("Incrementing...\n");
            count++;
        }
        if (expression[i] == ')') {
   //         printf("Decrementing...\n");
            count--; 
        }
        if (expression[i] == ' ') {
   //         printf("Encountered Delimiter %d\n", count);
            if (count == 0) {
                end = i; 
                Node* node = create_node(expression, start, end);
       //         printf("Pointers Returned: %p %p\n", tree, node);
                
                add_to_tree(tree, node);

                start = i+1;
            }
        }
    }
//    printf("tree--\n");
//    printf("%p\n", tree);
    return tree;
}

void print_tree(Node* tree, char* left_right) {
    Node* node = tree; 
    printf("Printing Node: %s\n" , left_right);

    if (node!=NULL) {
        int type = node->data->type;
        printf("TYPE: %d\n", type);
        if (type == SYMBOL) {
            printf("VALUE: %s\n\n", (char*)(node->data->value));
        } else {
            printf("VALUE: %d\n\n", *(int*)node->data->value);
        }
        print_tree(node->left, "Left");
        print_tree(node->right, "Right");
    } else {
        printf("(NIL)\n\n");
    }
}


void lisp(char* expression) {
    Node* parsed_tree = parse(expression);
    printf("\n\nPrinting Tree:\n-----------------\n");

    print_tree(parsed_tree, "Head");
    int result = evaluate(parsed_tree);

    printf("Result: %d\n", result);
    
}


int main(int argc, char* argv[]) {
    char* exp = (char*)malloc(4096);
    while (1) {
        fputs("psi> ", stdout);
        fgets(exp, 4096, stdin);
        // exp = "(/ 10 (+ 1 1 ) )";
        printf("Expression: %s\n", exp);
        lisp(exp);
    }
}