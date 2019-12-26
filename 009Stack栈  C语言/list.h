//
// Created by zhubin on 2019/1/24.
//

#ifndef STACK_LIST_H
#define STACK_LIST_H
#include <stdbool.h>
typedef struct ListElmts{
    void* data;
    struct ListElmts* next;
}ListElmt;
typedef struct Lists{
    int size;
    int (*match)(const void* key1,const void* key2);
    void (*destroy)(void* data);
    ListElmt * head;
    ListElmt* tail;
}List;
void destroy(void* data);
void list_destroy(List* list);
void list_init(List* list,void (*destroy)(void* data));//初始化链表
bool list_rem_next(List* list,ListElmt* element,void** data);
bool list_ins_next(List* list,ListElmt* element,const void* data);
#endif //STACK_LIST_H
