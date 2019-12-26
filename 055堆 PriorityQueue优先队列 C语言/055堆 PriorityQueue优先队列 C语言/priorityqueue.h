//
// Created by archlinux on 2019/7/31.
//

#ifndef HEAP_PRIORITYQUEUE_H
#define HEAP_PRIORITYQUEUE_H

#include "heap.h"

// 多态
typedef Heap PriorityQueue;

#define pqueue_init heap_init

#define pqueue_destroy heap_destroy

#define pqueue_insert heap_insert

#define pqueue_extract heap_extract

#define pqueue_peek(pqueue) ((pqueue)->tree == NULL?NULL:(pqueue)->tree[0])

#endif //HEAP_PRIORITYQUEUE_H
