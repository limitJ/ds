//
// Created by zhubin on 2019/1/24.
//
#include <stdlib.h>
#include <string.h>
#include "list.h"
void destroy(void* data){
    free(data);
}
bool list_rem_next(List* list,ListElmt* element,void** data){
    ListElmt* old_element;
    if (list->size == 0) {
        return false;
    }
    if (element == NULL) {
        *data = list->head->data;
        old_element = list->head;//当不指定移除具体项的时候 依次从头部开始移除
        list->head = list->head->next;
        if (list->size == 1) {
            list->tail = NULL;
        }
    }else{
        if (element->next == NULL) {
            return false;
        }
        *data = element->next->data;
        old_element = element->next;   //移除指定元素 并保存下来 以便于调用free释放节点
        element->next = old_element->next;//指向下一个元素的下一个元素
        if (element->next == NULL) {
            list->tail = element;
        }
    }
    free(old_element);
    list->size--;
    return true;
}

void list_init(List* list,void (*destroy)(void* data)){//初始化链表
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}
void list_destroy(List* list){//销毁链表
    while (list->size > 0) {
        if (list_rem_next(list, NULL, &list->head->data) == 0 && list->destroy != NULL) {
            list->destroy(&list->head->data); //如果初始化链表的时候destroy参数不为NULL则销毁链表的时候每次调用都会销毁数据
        }
    }
    memset(list, 0, sizeof(List));//将List指向的内存初始化 全部填充0
}
bool list_ins_next(List* list,ListElmt* element,const void* data){
    ListElmt* new_element;
    if ((new_element = (ListElmt *) malloc(sizeof(ListElmt))) == NULL) {
        return false;
    }
    new_element->data = (void*)data;
    if(element == NULL){
        if (list->size == 0) {
            list->tail = new_element;
        }
        new_element->next = list->head;  //如果没有传入element节点 则尾插法在头部添加数据
        list->head = new_element;        //链表头存放了数据也存放了指针域
    }else{
        if (element->next == NULL) {     //在指定element后插入一条新数据
            list->tail = new_element;    //如果尾部 则将tail值为NULL
        }
        new_element->next = element->next;
        element->next = new_element;
    }
    list->size++;
    return true;
}