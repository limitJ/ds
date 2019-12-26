#ifndef _LIST_H
#define _LIST_H 1
#include <stdbool.h>
typedef struct ListElmt_{
    void* data;
    struct ListElmt_* next;
}ListElmt;
typedef struct List_{
    int size;
    int (*compare)(const void* key1,const void* key2);
    void (*destroy)(void* data);
    ListElmt * head;
    ListElmt* tail;
}List;
void list_destroy(List* list);
void list_init(List* list,int (*compare)(const void* key1,const void* key2),void (*destroy)(void* data));
bool list_rem_next(List* list,ListElmt* element,void** data);
bool list_ins_next(List* list,ListElmt* element,const void* data);

#endif