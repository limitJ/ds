//
// Created by QQ 582521582 on 2019/5/19.
//
#include "queue.h"
void initQueue(Queue* queue){
    queue->size = 0;
    queue->head = NULL;
}
bool poll(Queue* queue,AdjList adjList){
    QueueElement *element = (QueueElement *) malloc(sizeof(QueueElement));
    if (element == NULL) {
        return false;
    }
    if (queue->head == NULL) {
        *element->adjList = *adjList;
        element->next = NULL;
        element->next = queue->head;
        queue->head = element;
    }else{
        *element->adjList = *adjList;
        element->next = queue->head;
        queue->head = element;
    }
    queue->size++;
    return true;
}
AdjList* pop(Queue* queue){
    if (queue->size == 0) {
        return false;
    }
    QueueElement* old_element = queue->head;
    queue->head = queue->head->next;
    queue->size--;
    return &old_element->adjList;
}
bool isEmpty(Queue* queue){
    return 0 == queue->size;
}
AdjList* peek(Queue* queue){
    return &queue->head->adjList;
}