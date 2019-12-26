/*
 *单链表
 * */
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>
#define len(arr) sizeof(arr)/sizeof(arr[0])
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
int match(const void* key1,const void* key2);
