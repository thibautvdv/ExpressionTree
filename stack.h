#ifndef STACK_H
#define STACK_H

#include <stdio.h>

#include "data_types.h"
#include "expression_tree.h"

// Toevoegen van een element aan de stack
// Stack is een pointer om de stack aan te passen van de main functie
// Anders is het enkel in deze scope aangepast
// Data is de data die we gaan toevoegen
void push(stack_t *stack, node* data);

// Waarde van de stack halen
node *pop(stack_t *stack);

// Stack leeg maken = alles op nul zetten
void clearStack(stack_t *stack);

void setupStack(stack_t *stack);

unsigned int stack_size(stack_t *stack);

#endif // STACK_H
