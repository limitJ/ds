//
// Created by zhubin on 2019/3/13.
//

#include "list.h"
bool initList(List* list){
    list->head = NULL;
    list->len = 0;
    list->tail = NULL;
    return true;
}
bool ins(List* list,int index,int data){
    if (index < 1 || index>list->len+1){
        throwExpection("��������Ԫ��Խ�磡\n");
        return false;
    }
    if (list->len+1 == index){//˵������λ���������ĩβ��
        return push(list,data);
    }else{
        ListElement* new_element = newObject(ListElement);
        if (new_element == NULL){
            throwExpection("�����ڴ�ʧ�ܣ�\n");
            return false;
        }
        new_element->data = data;
        ListElement* element = list->head;
        for (int i = 1; i < index-1; i++){
            element = element->next;
        }
        new_element->next = element->next;
        element->next = new_element;
    }
    list->len++;
    return true;
}
bool del(List* list, int index,int* data){
    if (index < 1 || index>list->len){
        throwExpection("ɾ������Ԫ��Խ�磡\n");
        return false;
    }
    ListElement* old_element = newObject(ListElement);
    if (old_element == NULL){
        throwExpection("�����ڴ�ʧ�ܣ�\n");
        return false;
    }
    if (1 == index){//�����Զ����ɾ��λ��1 �������ݽṹ�е�ջ
        return pop(list,data);
    }else{
        ListElement* element = list->head;
        for (int i = 1; i < index-1; i++){
            element = element->next;
        }
        old_element = element->next;
        *data = old_element->data;
        element->next = old_element->next;
        if (element->next == NULL){
            list->tail = element;
        }
        free(old_element);
    }
    --list->len;
    return true;
}
bool push(List* list,int data){
    ListElement* new_element = newObject(ListElement);
    if (new_element == NULL){
        throwExpection("�����ڴ�ʧ�ܣ�\n");
        return false;
    }
    new_element->data = data;
    if (list->len == 0) {
        list->tail = new_element;
    }
    new_element->next = list->head;
    list->head = new_element;
    ++list->len;
    return true;
}

bool pop(List* list,int* data){
    if (list->len == 0) {
        throwExpection("ջ�Ѿ�Ϊ�գ�\n");
        return false;
    }
    ListElement* old_element = newObject(ListElement);
    if (old_element == NULL) {
        throwExpection("�����ڴ�ʧ��\n");
        return false;
    }
    if(list->len == 1) {
        list->tail = NULL;
    }
    old_element = list->head;
    *data = old_element->data;
    list->head = list->head->next;
    free(old_element);
    --list->len;
    return true;
}
int peek(List* list){
    if (list->len == 0) {
        throwExpection("����ջ��Ϊ��!\n");
        return false;
    }
    return list->head->data;
}
int poll(List* list){
    if (list->len == 0) {
        throwExpection("����ջ��Ϊ��!\n");
        return false;
    }
    return list->tail->data;
}
void print(List* list){//Ĭ�ϴ�ӡ˳��������ͷ�巨���߼��ṹ ��ջ��˳���ӡ
    List element = *list;
    while (element.head != NULL){
        printf("%d ",element.head->data);
        element.head = element.head->next;
    }
    printf("\n");
}
void printQueue(ListElement* element){//�õݹ�ģ��Ķ��д�ӡ��
    if (element != NULL) {
        printQueue(element->next);
        printf("%d ", element->data);
    }else{
       return ;
    }
}
bool destroy(List* list){
    clearList(list);
    free(list->tail);
    free(list->head);
    free(list);
    return true;
}
bool clearList(List* list){
    int len = list->len;
    int element = 0;
    for (int i = 0; i < len; ++i) {
        pop(list,&element);
    }
    return true;
}
bool isEmpty(List* list){
    return 0 == list->len;
}
int getLength(List* list){
    return  list->len;
}
bool getElement(List* list,int index,int* element){
    List li = *list;
    if (index < 1 || index > list->len) {
        throwExpection("����Խ��!\n");
        return false;
    }
    for (int i = 0; i < index-1; ++i) {
        li.head = li.head->next;
    }
    *element = li.head->data;
    return true;
}
ListElement* getLocElement(ListElement* element,int data){
    if(element == NULL){
        throwExpection("����ջ�Ѿ�Ϊ��!\n");
        return NULL;
    }
    if(element->data == data){
        return element;
    }
    return getLocElement(element->next,data);
}
bool getNext(List* list,int index,int* data){
    List li = *list;
    if (index < 1 || index > list->len) {
        throwExpection("����Խ��!\n");
        return false;
    }
    if(index == list->len){
        throwExpection("�Ѿ������һ��Ԫ��,û�к��Ԫ��!\n");
        return false;
    }
    for (int i = 0; i < index-1; ++i) {
        li.head = li.head->next;
    }
    *data = li.head->next->data;
    return true;
}