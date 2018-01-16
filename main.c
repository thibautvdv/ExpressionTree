#include <stdio.h>
#include <stdlib.h>

#include "data_types.h"
#include "expression_tree.h"

int main(){

    // Uitlezen van input
    printf("Enter equation:\t");
    char equation[256];
    reset_buffer(equation, 256);

    int counter = -1;

    do{
        equation[++counter] = getchar();
    } while (equation[counter] != '\n' && counter < 256);

    // Binaire boom maken aan de hand van input
    node* tree = create_tree(equation);

    printf("%.2f\n", evaluate_tree(tree));

    free_node(tree);

    getchar();

    return 0;
}
