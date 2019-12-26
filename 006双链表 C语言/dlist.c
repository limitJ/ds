//
// Created by zhubin on 2019/1/19.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dlist.h"
void dlist_init(DList* list,void (*destroy)(void* data)){
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}
void dlist_destroy(DList* list){
    DListElmt* elmt = list->head;
    while (list->size > 0) {
        if (dlist_remove(list, elmt, elmt->data)==true&&list->destroy != NULL) {
            list->destroy(elmt->data);
            elmt = elmt->next;
        }
    }
    memset(list, 0, sizeof(DListElmt));
}
void destroy(void* data){
    free(data);
}
bool dlist_ins_next(DList* list,DListElmt* element,const void* data){
    DListElmt* new_element = (DListElmt*)malloc(sizeof(DListElmt));
    if (element == NULL && list->size != 0) {
        puts("element为NULLsize不为0");
        return false;
    }
    if (new_element == NULL) {
        puts("内存分配失败");
        return false;
    }
    new_element->data = (void *) data;
    if (list->size == 0) {
        list->head = new_element;
        list->head->last = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    }else{
        new_element->next = element->next;
        new_element->last = element;
        if (element->next == NULL) {
            list->tail = new_element;
        }else{
            element->next->last = new_element;
        }
        element->next = new_element;
    }
    list->size++;
    return true;
}
bool dlist_ins_last(DList* list, DListElmt* element, const void* data){
    DListElmt *new_element = (DListElmt *) malloc(sizeof(DListElmt));
    if (element == NULL && list->size != 0) {
        puts("element为NULLsize不为0");
        return false;
    }
    if (new_element == NULL) {
        puts("内存分配失败");
        return false;
    }
    new_element->data = (void*)data;
    if (list->size == 0) {
        list->head = new_element;
        list->head->last = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    } else {
        new_element->next = element;
        new_element->last = element->last;
        if (element->last == NULL) {
            list->head = new_element;
        } else {
            element->last->next = new_element;
        }
        element->last = new_element;
    }
    list->size++;
    return true;
}
bool dlist_remove(DList* list,DListElmt* element, const void** data){
    if (element == NULL && list->size != 0) {
        puts("element为NULLsize不为0");
        return false;
    }
    *data = element->data;
    if (element == list->head) {
        list->head = element->next;
        if (element->next == NULL) {
            list->tail = NULL;
        } else {
            list->head->last = NULL;
        }
    } else {
        element->last->next = element->next;
        if (element->next == NULL) {
            list->tail = element->last;
        } else {
            element->next->last = element->last;
        }
    }
    free(element);
    list->size--;
    return true;
}


