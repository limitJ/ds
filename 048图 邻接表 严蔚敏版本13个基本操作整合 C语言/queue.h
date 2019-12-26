//
// Created by QQ 582521582 on 2019/5/19.
//

#ifndef ADJMAP_QUEUE_H
#define ADJMAP_QUEUE_H

#include "adjmap.h"
typedef struct QueueElement{
    AdjList adjList;
    struct QueueElement* next;
}QueueElement;
typedef struct Queue{
    QueueElement* head;
    int size;
}Queue;
void initQueue(Queue* queue);
bool poll(Queue* queue,AdjList adjList);
AdjList* pop(Queue* queue);
bool isEmpty(Queue* queue);
#endif //ADJMAP_QUEUE_H
