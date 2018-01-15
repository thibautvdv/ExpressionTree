#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#define STACK_CAPACITY 16
#define QUEUE_CAPACITY 16

typedef struct node {
    int isOperator;
    char operation;
    float value;
    struct node *left;
    struct node *right;
} node;

typedef struct stack_t{
    node* data[STACK_CAPACITY];
    unsigned int MAX_CAPACITY;
    unsigned int current_index;
} stack_t;



typedef struct queue_t{
    node* data[QUEUE_CAPACITY];
    unsigned int MAX_CAPACITY;
    unsigned int current_index;
} queue_t;

#endif // DATA_TYPES_H
