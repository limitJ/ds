//
// Created by zhubin on 2019/1/22.
//

#ifndef CLIST_CLIST_H
#define CLIST_CLIST_H
#include <stdlib.h>
#include <stdbool.h>
typedef struct CListElmts{
    void* data;
    struct CListElmts* next;
}CListElmt;
typedef struct CLists{
    int size;
    CListElmt* head;
    void (*destroy)(const void *data);
}CList;
typedef struct LRU_{
    int number;
    int reference;
}LRU;
int rep(CListElmt** current);
void clist_init(CList* list,void (*destroy)(const void* data));//初始化链表
void clist_destroy(CList* list);//销毁循环链表
void destroy(void* data);//释放元素
bool clist_ins_next(CList* list,CListElmt* element,void* data);//插入元素
bool clist_rem_next(CList* list,CListElmt* element,void** data);//删除元素
#endif //CLIST_CLIST_H
