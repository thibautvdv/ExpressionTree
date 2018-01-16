#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

#include "data_types.h"
#include "stack.h"
#include "queue.h"

int isOperator(const char *c);
node* new_node(float value, char operation, int isOperator);
node *create_tree(const char *expression);
void reset_buffer(char *buffer, int size);

float evaluate_tree(node* tree_node);

void free_node(node* tree_node);


#endif // EXPRESSION_TREE_H
