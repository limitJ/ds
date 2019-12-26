//
// Created by zhubin on 2019/1/27.
//

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H
#include <stdlib.h>
#include <stdbool.h>
typedef struct ListElmts{
    void* data;
    struct ListElmts* next;
}ListElmt;
typedef struct Queues{
    ListElmt* head;
    ListElmt* tail;
    int size;
}Queue;
void initList(Queue* queue);
void queue_destroy(Queue* queue);
bool push(Queue* queue,void* data);
bool pop(Queue* queue);
void* peek(Queue* queue);
#endif //QUEUE_QUEUE_H
