#include "expression_tree.h"

// Met deze functie kunnen we controleren of een char een operator of een cijfer is
int isOperator(const char *c){
    if(*c == '+' || *c == '-' || *c == '*' || *c == '/' || *c == '(' || *c == ')' || *c == '^' || *c == '%'){
        return 1;
    } else {
        return 0;
    }
}

// Het aanmaken van een node kan door middel van deze functie
node* new_node(float value, char operation, int isOperator){
    node* temp_node = (node*)malloc(sizeof(node));

    if(temp_node == NULL){
        printf("Failed malloc");
        return 0;
    }

    temp_node->left = 0;
    temp_node->right = 0;

    temp_node->isOperator = isOperator;
    temp_node->value = value;
    temp_node->operation = operation;

    return temp_node;

}

node* create_tree(const char *expression){

    // De methode die we gebruiken is deels gebaseerd op de methode die we gezien hebben bij computersystemen
    // Het shunting-yard algoritme zorgt ervoor dat de vergelijking in post order in een queue komt
    // Aan de hand van deze notatie kunnen we een expressie boom maken
    // Het shunting-yard algoritme houdt rekenening met de volgorde van de bewerking

    // Voor het algoritme hebben we een stack en een queue nodig
    // Deze gebruik ik van de vorige opdracht
    // De waarde in de stack is een pointer naar een node
    queue_t queue;
    stack_t stack;

    setupQueue(&queue);
    setupStack(&stack);

    // Deze buffer gaan we gebruiken om tijdelijk cijfers op te slaan,
    // om hier later een getal mee te maken
    char buffer[100];
    reset_buffer(buffer,100);
    int buffer_counter = 0;

    // Pointer naar een node om tijdelijk een node in de functie te kunnen bijhouden
    node* tmpNode1;

    // Counter om te zien waar we in onze expressie zijn
    int i = 0;

    // Variabele om bij te houden of dat er nog een getal in de buffer zit of niet
    int vorige_was_getal = 0;

    while(*(expression+i) != 0 && *(expression+i) != '\n'){
        if(!isOperator((expression+i))){
            // Als het een cijfer is, dan slaan we dit op in onze buffer
            *(buffer + buffer_counter++) = *(expression + i);
            vorige_was_getal = 1; // Er zit een getal in de buffer
        } else {

            // Als er een getal in onze buffer zit, dan moet die naar de queue
            if(vorige_was_getal){
                tmpNode1 = new_node(atof(buffer), 0, 0);
                reset_buffer(buffer, 100);
                buffer_counter = 0;
                enqueue(&queue, tmpNode1);
            }


            // Node aanmaken met onze operator
            tmpNode1 = new_node(0, *(expression+i), 1);


            // Als het een +, -, *, / of % is, dan moet men kijken naar de volgorde van de bewerking
            if(*(expression+i) == '*' || *(expression+i) == '/' || *(expression+i) == '%'){
                // Als de stack leeg is, dan moeten we operator gewoon op de stack plaatsen
                // Anders moet er gekeken worden naar de volgorde van de bewerking
                if(stack_size(&stack) != 0){
                    if(stack.data[stack.current_index-1]->operation == '*' || stack.data[stack.current_index-1]->operation == '/' || stack.data[stack.current_index-1]->operation == '%' || stack.data[stack.current_index-1]->operation == '^'){
                        enqueue(&queue, pop(&stack));
                        push(&stack, tmpNode1);
                    } else {
                        // Als er op de stack een + of - staat, dan mag *, / of % gewoon op de stack geplaatst worden
                        push(&stack, tmpNode1);
                    }
                } else {
                    // Als er nog niets op de stack staat, gewoon op de stack plaatsen dan
                    push(&stack, tmpNode1);
                }
            } else if(*(expression+i) == ')') {
                // Als we ) tegenkomen, dan mag alles van de stack naar de queue totdat een ( gevonden wordt
                node *tmpNode2 = pop(&stack);
                while(tmpNode2->operation != '('){
                    enqueue(&queue, tmpNode2);
                    tmpNode2 = pop(&stack);
                }
            } else if (*(expression+i) == '+' || *(expression+i) == '-') {
                if(stack_size(&stack) != 0){
                    if(stack.data[stack.current_index-1]->operation == '^'){
                        enqueue(&queue, pop(&stack));
                        push(&stack, tmpNode1);
                    } else {
                        push(&stack, tmpNode1);
                    }
                } else {
                    push(&stack, tmpNode1);
                }
            } else {
                push(&stack, tmpNode1);
            }

            vorige_was_getal = 0;
        }
        i++;
    }

    // Als er nog een getal in onze buffer zat, dan moet deze naar de queue
    if(vorige_was_getal){
        tmpNode1 = new_node(atof(buffer), 0, 0);
        enqueue(&queue, tmpNode1);
    }

    // Alles op de stack moet naar de queue
    while(stack_size(&stack) != 0){
        enqueue(&queue, pop(&stack));
    }

    // Nu hebben we de post order van de vergelijking
    // Hiervan kunnen we een goede expression tree maken
    // We gebruiken hiervoor ook de stack
    // De stack zou nu leeg moeten zijn
    // Op het einde van de while loop zou de root node van de expression tree op de stack zijn

    // We gaan onze queue leeg maken
    while(queue_size(&queue) != 0){
        tmpNode1 = dequeue(&queue);

        // Als onze node uit de queue een operator is,
        // dan zijn TOS en SOS normaal getallen
        // Deze getallen worden rechter en linker kinderen van de operator node
        // De operator node plaatsen we daarna weer op de stack
        if(tmpNode1->isOperator){
            tmpNode1->right = pop(&stack);
            tmpNode1->left = pop(&stack);
            push(&stack, tmpNode1);
        } else {
            // Als de node uit de queue een getal is, dan plaatsen we deze op de stack
            push(&stack, tmpNode1);
        }
    }

    // De stack bestaat alleen nog maar uit de root node van onze expressie boom
    // Deze retourneren we dus
    return pop(&stack);
}

// Recursieve functie om van een expressie boom naar een uitkomst te gaan
float evaluate_tree(node *tree_node){
    if(tree_node != 0){
            if (tree_node->isOperator){
                switch (tree_node->operation) {
                case '+':
                    return evaluate_tree(tree_node->left) + evaluate_tree(tree_node->right);
                case '-':
                    return evaluate_tree(tree_node->left) - evaluate_tree(tree_node->right);
                case '*':
                    return evaluate_tree(tree_node->left) * evaluate_tree(tree_node->right);
                case '/':
                    return evaluate_tree(tree_node->left) / evaluate_tree(tree_node->right);
                case '%':
                    return (int)(evaluate_tree(tree_node->left)) % (int)(evaluate_tree(tree_node->right));
                case '^':
                    return powf(evaluate_tree(tree_node->left), evaluate_tree(tree_node->right));
                }
            } else{
                return tree_node->value;
            }
        }

        return 0;
}

// Deze functie zet alle waarden in een char array op 0
void reset_buffer(char *buffer, int size){
    for(int i = 0; i < size; i++){
        *(buffer+i) = 0;
    }
}
