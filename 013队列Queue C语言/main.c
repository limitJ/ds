/*
 * QQ: 582521582
 * QQȺ: 322085520
 * ����Queue ����β�巨����һ�ֶ���
 * */
#include <stdio.h>
#include "queue.h"
#define len(arr) sizeof(arr)/sizeof(arr[0])
int main() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    initList(queue);
    int QQ[] = {
            5,8,2,5,2,1,5,8,2
    };
    for (int i = 0; i < len(QQ); ++i) {
        push(queue, &QQ[i]);
    }
    printf("����˳�� ");
    while (queue->head != NULL) {
        printf("%d ", *(int *) peek(queue));
        pop(queue);
    }
    return 0;
}