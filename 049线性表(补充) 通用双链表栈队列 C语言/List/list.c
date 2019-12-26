/*
 * Created by QQ 582521582 on 2019/7/22.
 * QQ群 322085520
 * 链表实现c文件
**/
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

//宏定义 抛异常警告
#define throwException(e) fputs(e,stderr)

void list_init(List* list,void (*destroy)(void* data)){
    if (list == NULL){
        throwException("警告:list不能为空！\n");
        return;
    }
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

void list_destroy(List* list){
    void* data;
    while(!isEmpty(list)){
        if (delete(list, list->head, (void**)&data) && list->destroy!=NULL){
            list->destroy(data);
        }
    }
    free(list);
}

bool insert(List* list,ListElement* element,void* data){
    //待插入的新元素
    ListElement* new_element = (ListElement *) malloc(sizeof(ListElement));
    if (new_element == NULL) {
        throwException("警告：分配内存失败\n");
        return false;
    }
    new_element->next = NULL;
    new_element->prev = NULL;
    new_element->data = data;
    if (isEmpty(list)) {
        //第一次插入的时候 先初始化一下头尾节点
        list->head = new_element;
        //只有一个元素的时候插入头节点就等于尾节点
        list->tail = list->head;
    }else{
        if (element == NULL) {
            //头插法 对应数据结构 栈 (删除从头部删)
            list->head->prev = new_element;
            new_element->next = list->head;
            //头插法 就是每次都把新插入元素变成头结点
            list->head = new_element;
        }else if (isTail(list,element)) {
            //尾插法 对应数据结构 队列 (删除从头部删)
            list->tail->next = new_element;
            new_element->prev = list->tail;
            //尾插法 就是把每次新插入的元素变成尾节点
            list->tail = new_element;
        }else{
            //正常的链表插入
            new_element->next = element->next;
            new_element->prev = element;
            element->next->prev = new_element;
            element->next = new_element;
        }
    }
    //链表元素数量+1
    list->size++;
    return true;
}

bool delete(List* list,ListElement* element, void** data){
    //保存被删元素
    ListElement* old_element = NULL;
    if (isEmpty(list)) {
        throwException("没有元素可删\n");
        return false;
    }
    //删除头部
    if (isHead(list,element)) {
        //保存下被删的数据
        *data = list->head->data;
        old_element = list->head;
        list->head = element->next;
        //如果此时的head刚好是最后一个元素的时候 记得删除掉维护的尾指针指向 防止内存泄露
        if (list->head == NULL) {
            list->tail = NULL;
        }
    } else if(isTail(list,element)){
        //从尾部删除 比如和插入方式配合 可以实现tcp ip协议中的滑动窗口算法
        *data = list->tail->data;
        old_element = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        old_element->prev = NULL;
    }else{
        *data = element->data;
        old_element = element;
        element->prev->next = old_element->next;
        element->next->prev = old_element->prev;
        old_element->next = NULL;
        old_element->prev = NULL;

    }
    free(old_element);
    list->size--;
    return true;
}


bool isEmpty(List* list){
    return 0 == list->size;
}

bool isHead(List* list,ListElement* element){
    return list->head == element;
}

bool isTail(List* list,ListElement* element){
    return list->tail == element && element->next == NULL;
}