
#include "queue.h"

void clearQueue(queue_t *queue){
    for(unsigned int i = 0; i < queue->MAX_CAPACITY; i++){
        queue->data[i] = 0;
    }
}

void setupQueue(queue_t *queue){
    queue->current_index = 0;
    queue->MAX_CAPACITY = QUEUE_CAPACITY;
    clearQueue(queue);
}

void enqueue(queue_t *queue, node* data){
    if(queue->current_index == queue->MAX_CAPACITY){
        printf("Queue is full\n");
    } else {
        queue->data[queue->current_index++] = data;
    }
}

node* dequeue(queue_t *queue){
    if(queue->current_index == 0){
        printf("Nothing in the queue\n");
        return 0;
    } else {
        node* temp_data = queue->data[0];
        queue->current_index--;

        for(unsigned int i = 0; i < queue->current_index; i++){
            queue->data[i] = queue->data[i+1];
        }
        return temp_data;
    }
}

unsigned int queue_size(queue_t *queue){
    return queue->current_index;
}
