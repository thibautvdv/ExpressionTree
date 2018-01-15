
#include "stack.h"

unsigned int stack_size(stack_t *stack){
    return stack->current_index;
}


// Toevoegen van een element aan de stack
// Stack is een pointer om de stack aan te passen van de main functie
// Anders is het enkel in deze scope aangepast
// Data is de data die we gaan toevoegen
void push(stack_t *stack, node* data){
    if(stack->current_index == stack->MAX_CAPACITY){
        printf("Stack is full\n");
    } else {
        stack->data[stack->current_index++] = data; // Data toevoegen
    }
}

// Waarde van de stack halen
node* pop(stack_t *stack){
    if(stack->current_index == 0){
        printf("Nothing in the stack\n");
        return 0;
    } else {
        return stack->data[--stack->current_index]; // Eerst index - 1, daarna waarde retourneren.
    }
}

// Stack leeg maken = alles op nul zetten
void clearStack(stack_t *stack){
    for(unsigned int i = 0; i < stack->MAX_CAPACITY; i++){
        stack->data[i] = 0;
    }
}

// Set default values voor de stack
void setupStack(stack_t *stack){
    stack->current_index = 0;
    stack->MAX_CAPACITY = STACK_CAPACITY;
    clearStack(stack);
}
