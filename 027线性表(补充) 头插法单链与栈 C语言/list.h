//
// Created by zhubin on 2019/3/13.
//
#ifndef LIST_LIST_H
#define LIST_LIST_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define throwExpection(e) fputs(e,stderr);
#define newObject(Object) (Object*)malloc(sizeof(Object));
#define len(arr) sizeof(arr)/sizeof(arr[0])
#define boolean(flag) flag==true?"true":"false"
typedef struct ListElement{
    int data; //数据
    struct ListElement* next;//下一个节点
}ListElement;
typedef struct List{
    ListElement* head;//链表头节点
    ListElement* tail;//链表尾节点
    int len;//链表长度
}List;
bool initList(List* list);//初始化链表
bool destroy(List* list); //销毁链表
bool clearList(List* list);//清空链表元素
bool isEmpty(List* list); //检查是否为空
int getLength(List* list); //获得链表节点长度
bool getElement(List* list,int index,int* element); //获取指定节点的元素
ListElement* getLocElement(ListElement* list,int data);//获取与指定元素相等的第一个节点元素 如果没有返回NULL
bool getNext(List* list,int index,int* data);//获取指定位置节点的后驱节点
bool ins(List* List, int index, int data);//指定位置插入元素
bool del(List* list, int index,int* data);//指定位置删除元素
void print(List* list);//打印链表 注意由于是头插法链表 所以打印顺序 是出栈顺序 先进后出
bool push(List* list,int data);//栈顶添加元素
bool pop(List* list,int* data);//移除栈顶你元素 并返回移除元素
int peek(List* list); //获取栈顶元素
int poll(List* list); //获取栈尾元素
void printQueue(ListElement* element);//用递归方式 用队列的顺序 输出链表节点元素！
#endif