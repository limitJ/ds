//
// Created by archlinux on 2019/7/30.
//

#include <stdlib.h>
#include <memory.h>
#include "heap.h"

void heap_init(Heap *heap, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data)){
    heap->size = 0;
    heap->compare = compare;
    heap->destroy = destroy;
    heap->tree = NULL;
}

int heap_insert(Heap *heap, const void *data){
    void* temp;
    int ipos;
    int ppos;
    temp = (void**)realloc(heap->tree,(heap->size+1)* sizeof(void*));
    if (temp == NULL) {
        return -1;
    }else{
        heap->tree = temp;
    }
    //每次都是先插入最后一个元素的地方
    heap->tree[heap->size] = (void*)data;
    ipos = heap->size;
    ppos = heap_parent(ipos);//找到插入最后一个节点的父亲节点在数组中的坐标
    while(ipos > 0 && heap->compare(heap->tree[ppos],heap->tree[ipos])<0){
        //调整最后一个的元素在堆中的次序
        temp = heap->tree[ppos];
        heap->tree[ppos] = heap->tree[ipos];
        heap->tree[ipos] = temp;
        ipos = ppos;
        ppos = heap_parent(ipos);
    }
    heap->size++;
    return 0;
}

//移除堆顶部的数据 返回给data
int heap_extract(Heap *heap,   void **data){
    void* save;
    void* temp;
    int ipos;
    int lpos;
    int rpos;
    int mpos;
    if (heap->size == 0) {
        return -1;
    }
    /*
     * 移除堆顶元素 会影响堆结构 处理时候 应该将最后一个元素放到顶部 然后往下浮动 直到满足堆结构
     * */
    *data = heap->tree[0];
    //先保存下最后一个堆元素
    save = heap->tree[heap->size - 1];
    if (heap->size - 1 > 0) {
        temp = (void**)realloc(heap->tree,(heap->size)* sizeof(void*));
        if (temp == NULL) {
            return -1;
        }else{
            heap->tree = temp;
        }
        heap->size--;
    }else{
        //说明堆还剩下最后一个元素了
        free(heap->tree);
        heap->tree = NULL;
        heap->size = 0;
        return 0;
    }
    heap->tree[0] = save;
    ipos = 0;
    while(1){
        lpos = heap_left(ipos);//左孩子
        rpos = heap_right(ipos);//右孩子
        if (lpos<heap->size && heap->compare(heap->tree[lpos],heap->tree[ipos])>0){
            mpos = lpos;//先记录下左孩子在数组中的坐标
        }else{
            //说明比较通过左孩子
            mpos = ipos;
        }
        if (rpos<heap->size && heap->compare(heap->tree[rpos],heap->tree[mpos])>0){
            //这个if加上前面的ifelse 意思是将顶堆元素与左右孩子比较 比如在大顶堆为例 下浮应该与2个孩子中最大的地方下浮
            mpos = rpos;//先记录下左孩子在数组中的坐标
        }
        if (mpos == ipos){
            break;//这个说明新顶堆 不用下浮 都没有通过与左右孩子的比较
        }else{
            //否则下浮 下浮位置已经在mpos中确定
            temp = heap->tree[mpos];
            heap->tree[mpos] = heap->tree[ipos];
            heap->tree[ipos] = temp;
            ipos = mpos;
        }
    }
    return 0;
}

void heap_destroy(Heap* heap){
    if (heap->destroy != NULL) {
        for (int i = 0; i < heap->size; ++i) {
            heap->destroy(heap->tree[i]);
        }
    }
    free(heap->tree);
    memset(heap, 0, sizeof(Heap));
}