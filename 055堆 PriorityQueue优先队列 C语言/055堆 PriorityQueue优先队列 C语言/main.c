/*
 * 数据结构
 * 堆 优先队列
 * 优先队列实质上就是堆
 * 操作上是一模一样的
 *
 * 优先队列插入顺序是乱序插入的
 * 但是出队顺序确实按照顺序出队的
 *
 * 是一个非常有用的数据结构
 *
 * 编译器 LLVM CLang v8.0
 * C标准 c11
 * IDE CLion v2019-2
 * 运行平台 ArchLinux DDE
 * QQ：582521582
 * QQ群：322085520
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include "priorityqueue.h"

#define len(arr) ((int)(sizeof(typeof(arr))/sizeof(typeof(arr[0]))))
int compare(const void* key1,const void* key2);
void destroy(void* data);
int main(void) {
    PriorityQueue *pqueue = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    pqueue_init(pqueue, &compare, &destroy);
    int arr[] = {2,20,12,17,19,10,12,125,7,9,18};
    for (int i = 0; i < len(arr); ++i) {
        pqueue_insert(pqueue,&arr[i]);
    }
    printf("优先队列插入数据是乱序的\n");
    for (int i = 0; i < pqueue->size; ++i) {
        printf("%d ", *(int *) pqueue->tree[i]);
    }
    printf("\n优先队列出队顺序是有序的\n");
    while (pqueue_peek(pqueue)!=NULL && pqueue->size != 0) {
        void* data;
        printf("%d ", *(int *) pqueue_peek(pqueue));
        pqueue_extract(pqueue, &data);
    }
    return 0;
}
int compare(const void* key1,const void* key2){
    return *(int*)key1 - *(int*)key2;
}
void destroy(void* data){
    //NULL
}