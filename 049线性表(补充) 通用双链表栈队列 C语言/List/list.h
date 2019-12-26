/*
 * Created by QQ 582521582 on 2019/7/22.
 * QQ群 322085520
 * 单链表头文件
**/

#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <stdbool.h>

//链表存放元素结构体
typedef struct ListElement_{
    //C语言泛型指针数据 用于存数据
    void* data;
    //链表指针域 指向后一个节点
    struct ListElement_* next;
    //链表指针域 指向接一个节点
    struct ListElement_* prev;
}ListElement;

//链表结构体
typedef struct List_{
    //size链表元素的个数
    int size;
    //链表头结点
    ListElement* head;
    //链表尾节点
    ListElement* tail;
    //指针函数 用于用户自己自定义'比较'方法
    int (*compare)(const void* key1, const void* key2);
    //销毁链表元素函数 由用户自定义
    void (*destroy)(void* data);
}List;

/*
 * 以下为链表公共实现函数声明
 * */

/*
 * 链表的初始化
 * 参数1：传入链表
 * 参数2：用户自定义销毁函数 每次删除元素节点的时候 会调用这个销毁函数 传入是NULL则不销毁
 * */
extern void list_init(List* list,void (*destroy)(void* data));

/*
 * 销毁整个链表
 * 参数1：传入链表
 * */
extern void list_destroy(List* list);

/*
 * 在指定位置添加元素
 * 参数1：传入链表
 * 参数2：待添加位置
 * 参数3：待添加元素
 * */
extern bool insert(List* list,ListElement* element, void* data);

/*
 * 删除指定位置元素
 * 参数1：传入链表
 * 参数2：该元素下一个位置的待删除元素
 * 参数3：被删除元素
 * */
extern bool delete(List* list,ListElement* element, void** data);


/*
 * 判断链表是否需为空
 * 参数1：传入链表
 * */
extern bool isEmpty(List* list);

/*
 * 判断是否为头节点
 * 参数1：传入链表
 * 参数2：传入待验证元素
 * */
extern bool isHead(List* list,ListElement* element);

/*
 * 判断是否为尾节点
 * 参数1：传入链表
 * 参数2：传入待验证元素
 * */
extern bool isTail(List* list,ListElement* element);


#endif //LIST_LIST_H
