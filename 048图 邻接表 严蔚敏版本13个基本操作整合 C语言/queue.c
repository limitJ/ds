//
// Created by QQ 582521582 on 2019/5/19.
//
#include "queue.h"
/*
 * @param 队列queue
 * @result 初始化队列
 * */
void initQueue(Queue* queue){
    queue->size = 0;
    queue->head = NULL;
}

/*
 *@param 队列queue 图顶点结构体adjList
 *@result 将图顶点信息插入队列节点 按照头插法的方式插入 每次从头插入
 * */
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

/*
 *@param 队列queue
 *@result 删除队列头结点 并返回头结点中的adjList信息 并且使被删除的下一个节点称为新的头结点
 **/
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