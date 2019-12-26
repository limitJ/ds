/*
 *
 * 数据结构 堆
 * 堆
 * 有几个比较重要的点
 * 首先堆的移除 每次都是从顶堆移除 将新的元素补到顶堆 然后下浮 调整堆结构
 * 每次补元素 都是从堆的最后一个节点找到 然后补到顶堆
 * 而堆是一个二叉树结构 每次找最后一个节点 常规的使用层序遍历可以找到最后一个节点 不高效
 * 因此堆普遍采用数组结构来存储二叉树
 * 数组的优点 快速找到二叉树中最后一个元素 快速定位到父亲节点和孩子节点在数组中的位置
 * 因此 有以下几个关于二叉树的重要性质 和 结论
 * 在数组中
 * 快速定位父亲节点 (i-1)/2  i是数组中的下表
 * 快速定位左孩子点 i*2+1
 * 快速定位左孩子点 i*2+2
 * 快速定位顶堆元素 heap[0]
 * 快速定位堆尾元素 heap[heap->size-1]
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

#define len(arr) ((int)(sizeof(typeof(arr))/sizeof(typeof(arr[0]))))
int compare(const void* key1,const void* key2);
void destroy(void* data);
int pow2(int num);
int main(void) {
    Heap *heap = (Heap *) malloc(sizeof(Heap));
    heap_init(heap, &compare, &destroy);
    int arr[] = {25,20,22,17,19,10,12,15,7,9,18};
    for (int i = 0; i < len(arr); ++i) {
        heap_insert(heap,&arr[i]);
    }
    printf("插入一堆数据\n");
    for (int i = 0; i < heap->size; ++i) {
        printf("%d ", *(int *) heap->tree[i]);
    }
    void* data;
    heap_extract(heap, &data);
    printf("\n移除顶堆后\n");
    for (int i = 0; i < heap->size; ++i) {
        printf("%d ", *(int *) heap->tree[i]);
    }
    return 0;
}
int compare(const void* key1,const void* key2){
    return *(int*)key1 - *(int*)key2;
}
void destroy(void* data){
    free(data);
}