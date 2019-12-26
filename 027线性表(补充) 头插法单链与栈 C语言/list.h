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
    int data; //����
    struct ListElement* next;//��һ���ڵ�
}ListElement;
typedef struct List{
    ListElement* head;//����ͷ�ڵ�
    ListElement* tail;//����β�ڵ�
    int len;//������
}List;
bool initList(List* list);//��ʼ������
bool destroy(List* list); //��������
bool clearList(List* list);//�������Ԫ��
bool isEmpty(List* list); //����Ƿ�Ϊ��
int getLength(List* list); //�������ڵ㳤��
bool getElement(List* list,int index,int* element); //��ȡָ���ڵ��Ԫ��
ListElement* getLocElement(ListElement* list,int data);//��ȡ��ָ��Ԫ����ȵĵ�һ���ڵ�Ԫ�� ���û�з���NULL
bool getNext(List* list,int index,int* data);//��ȡָ��λ�ýڵ�ĺ����ڵ�
bool ins(List* List, int index, int data);//ָ��λ�ò���Ԫ��
bool del(List* list, int index,int* data);//ָ��λ��ɾ��Ԫ��
void print(List* list);//��ӡ���� ע��������ͷ�巨���� ���Դ�ӡ˳�� �ǳ�ջ˳�� �Ƚ����
bool push(List* list,int data);//ջ�����Ԫ��
bool pop(List* list,int* data);//�Ƴ�ջ����Ԫ�� �������Ƴ�Ԫ��
int peek(List* list); //��ȡջ��Ԫ��
int poll(List* list); //��ȡջβԪ��
void printQueue(ListElement* element);//�õݹ鷽ʽ �ö��е�˳�� �������ڵ�Ԫ�أ�
#endif