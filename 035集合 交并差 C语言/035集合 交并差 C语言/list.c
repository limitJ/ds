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
        old_element = list->head;//����ָ���Ƴ��������ʱ�� ���δ�ͷ����ʼ�Ƴ�
        list->head = list->head->next;
        if (list->size == 1) {
            list->tail = NULL;
        }
    }else{
        if (element->next == NULL) {
            return false;
        }
        *data = element->next->data;
        old_element = element->next;   //�Ƴ�ָ��Ԫ�� ���������� �Ա��ڵ���free�ͷŽڵ�
        element->next = old_element->next;//ָ����һ��Ԫ�ص���һ��Ԫ��
        if (element->next == NULL) {
            list->tail = element;
        }
    }
    free(old_element);
    list->size--;
    return true;
}

void list_init(List* list,void (*destroy)(void* data)){//��ʼ������
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}
void list_destroy(List* list){//��������
    while (list->size > 0) {
        if (list_rem_next(list, NULL, &list->head->data) == 0 && list->destroy != NULL) {
            list->destroy(&list->head->data); //�����ʼ�������ʱ��destroy������ΪNULL�����������ʱ��ÿ�ε��ö�����������
        }
    }
    memset(list, 0, sizeof(List));//��Listָ����ڴ��ʼ�� ȫ�����0
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
        new_element->next = list->head;  //���û�д���element�ڵ� ��β�巨��ͷ���������
        list->head = new_element;        //����ͷ���������Ҳ�����ָ����
    }else{
        if (element->next == NULL) {     //��ָ��element�����һ��������
            list->tail = new_element;    //���β�� ��tailֵΪNULL
        }
        new_element->next = element->next;
        element->next = new_element;
    }
    list->size++;
    return true;
}
