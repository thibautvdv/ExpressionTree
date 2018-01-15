#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>

#include "data_types.h"

void clearQueue(queue_t *queue);
void setupQueue(queue_t *queue);

void enqueue(queue_t *queue, node* data);
node* dequeue(queue_t *queue);
unsigned int queue_size(queue_t *queue);


#endif // QUEUE_H
