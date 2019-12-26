//
// Created by QQ 582521582 on 2019/4/17.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define len(arr) sizeof(arr)/sizeof(arr[0])
#define throwException(e) fprintf(stderr,e)
#define new(Object) (Object*)malloc(sizeof(Object))
#define boolean(flag) flag==true?"true":"false"
typedef struct ListElement{
    void* data;//泛型数据
    struct ListElement* next;//指针域
}ListElement;
typedef struct List{
    int size;//节点长度
    ListElement* head;//头节点 头结点也存放数据
    ListElement* tail;//尾节点
    int (*compare)(const void* key1, const void* key2);
    void (*destroy)(void* data);
}List;
void init_list(List* list,void (*destroy)(void* data));
bool insert(List* list,ListElement* element,ListElement* new_element);
ListElement* createNode(const void* data);
ListElement* delete(List* list,ListElement* element);
void dispose(ListElement* element);
ListElement* find(List* list,const void* data,int (*compare)(const void*, const void*));
bool isEmpty(List* list);
void list_destroy(List* list);
int getLoc(List* list,ListElement* element);
#endif //LIST_LIST_H
