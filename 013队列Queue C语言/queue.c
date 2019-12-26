//
// Created by zhubin on 2019/1/27.
//
#include "queue.h"
#include <stdio.h>
#include <string.h>
void initList(Queue* queue){
    queue->head = (ListElmt*)malloc(sizeof(ListElmt));
    queue->tail = NULL;
    queue->size = 0;
}
void queue_destroy(Queue* queue){
    while (queue->size != 0) {
        pop(queue);
    }
    memset(queue,0, sizeof(queue));
}
bool push(Queue* queue,void* data){
    if (queue->size == 0) {
        queue->head->data = data;
        queue->tail = queue->head;
        queue->tail->next = NULL;
    }else{
        ListElmt *new_element = (ListElmt *) malloc(sizeof(ListElmt));
        if (new_element == NULL) {
            puts("内存分配失败");
            return false;
        }
        new_element->data = data;
        queue->tail->next = new_element;
        queue->tail = new_element;
        queue->tail->next = NULL;
    }
    queue->size++;
    return true;
}
bool pop(Queue* queue){
    if (queue->size == 0) {
        puts("栈空!");
        return false;
    }
    if (queue->size == 1) {
        queue->tail = NULL;
    }
    ListElmt *old_element = queue->head;
    queue->head = queue->head->next;
    queue->size--;
    free(old_element);
    return true;

}
void* peek(Queue* queue){
    return  queue->head ==NULL?NULL:queue->head->data;
}
