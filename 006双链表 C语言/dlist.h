//
// Created by zhubin on 2019/1/19.
//

#ifndef DLIST_DLIST_H
#define DLIST_DLIST_H
#include <stdlib.h>
#include <stdbool.h>
typedef struct DListElmts{
    void* data;
    struct DListElmts* last;
    struct DListElmts* next;
}DListElmt;
typedef struct DLists{
    int size;
    void (*destroy)(void* data);
    DListElmt* head;
    DListElmt* tail;
}DList;
void destroy(void* data);
void dlist_init(DList* List,void (*destroy)(void* data));
void dlist_destroy(DList* list);
bool dlist_ins_next(DList* list,DListElmt* element,const void* data);
bool dlist_ins_last(DList* list,DListElmt* element, const void* data);
bool dlist_remove(DList* list,DListElmt* element, const void** data);
#endif //DLIST_DLIST_H
