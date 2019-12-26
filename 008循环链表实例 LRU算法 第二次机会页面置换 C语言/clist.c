//QQ: 582521582
//QQ群: 32205820
// Created by zhubin on 2019/1/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clist.h"
void clist_init(CList* list,void (*destroy)(const void* data)){
    list->size  = 0;
    list->destroy = destroy;
    list->head = NULL;
}
void clist_destroy(CList* list){
    void* data;
    while (list->size > 0) {
        if (clist_rem_next(list, NULL, (void **) &data) == true && list->destroy!= NULL) {
            list->destroy(data);
        }
    }
    memset(list, 0, sizeof(CList));
}
void destroy(void* data){
    free(data);
}
bool clist_ins_next(CList* list,CListElmt* element,void* data){
    CListElmt *new_element = (CListElmt *) malloc(sizeof(CListElmt));
    if (new_element == NULL) {
        puts("内存分配失败");
        return false;
    }
    new_element->data = (void *) data;
    if (list->size == 0) {
        new_element->next = list->head;
        list->head = new_element;
    } else{
        new_element->next = element->next;
        element->next = new_element;
    }
    list->size++;
    return true;
}
bool clist_rem_next(CList* list,CListElmt* element,void** data){
    CListElmt *old_element;
    if (list->size == 0) {
        puts("链表中没有元素,删除失败!");
        return false;
    }
    *data = element->next->data;
    if (element->next == element) { //下一个节点还是自己 说明该循环链表只有一个元素 next还是指向自己
        old_element = element->next;
        list->head = NULL;
    } else{
        old_element = element->next;
        element->next = element->next->next;
        if (old_element == list->head) { //如果element是循环链表的最后一个元素
            list->head = old_element->next; //则让头节点的下一个节点成为新的头节点
        }
    }
    free(old_element);
    list->size--;
    return true;
}
int rep(CListElmt** current){
    while (((LRU *) (*current)->data)->reference != 0) {
        *current = (*current)->next;//注意结合律 *current要括号括起来!
    }
    return ((LRU*)(*current)->data)->number;
}