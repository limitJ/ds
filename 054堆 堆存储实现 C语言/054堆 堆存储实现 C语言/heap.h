//
// Created by archlinux on 2019/7/30.
//

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H
typedef struct Heap_{
    int size;
    int (*compare)(const void* key1,const void* key2);
    void (*destroy)(void* data);
    void **tree;
}Heap;

void heap_init(Heap* heap,int (*compare)(const void* key1,const void* key2),void (*destroy)(void* data));

void heap_destroy(Heap* heap);

int heap_insert(Heap* heap, const void* data);

int heap_extract(Heap* heap,void** data);

#define heap_parent(npos) ((int)(((npos)-1)/2))

#define heap_left(npos) (((npos)*2)+1)

#define heap_right(npos) (((npos)*2)+2)
#endif //HEAP_HEAP_H
