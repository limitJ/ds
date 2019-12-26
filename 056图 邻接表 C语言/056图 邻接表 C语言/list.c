#include <stdlib.h>
#include <string.h>
#include "list.h"
bool list_rem_next(List* list,ListElmt* element,void** data){
    ListElmt* old_element;
    if (list->size == 0) {
        return false;
    }
    if (element == NULL) {
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;
        if (list->size == 1) {
            list->tail = NULL;
        }
    }else{
        if (element->next == NULL) {
            return false;
        }
        *data = element->next->data;
        old_element = element->next;
        element->next = old_element->next;
        if (element->next == NULL) {
            list->tail = element;
        }
    }
    free(old_element);
    list->size--;
    return true;
}

void list_init(List* list,int ((*compare)(const void* key1, const void* key2)),void (*destroy)(void* data)){
    list->size = 0;
    list->destroy = destroy;
    list->compare = compare;
    list->head = NULL;
    list->tail = NULL;
}
void list_destroy(List* list){
    while (list->size > 0) {
        if (list_rem_next(list, NULL, &list->head->data) == 0 && list->destroy != NULL) {
            list->destroy(&list->head->data);
        }
    }
    memset(list, 0, sizeof(List));
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
        new_element->next = list->head;
        list->head = new_element;
    }else{
        if (element->next == NULL) {
            list->tail = new_element;
        }
        new_element->next = element->next;
        element->next = new_element;
    }
    list->size++;
    return true;
}
