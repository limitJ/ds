/*
 * 循环链表
 * */
#include <stdio.h>
#include "clist.h"
#define len(arr) sizeof(arr)/sizeof(arr[0])
int main() {
    CList *list = (CList *) malloc(sizeof(CList));
    clist_init(list, NULL);
    int QQ[] = {
            5,8,2,5,2,1,5,8,2
    };
    clist_ins_next(list, list->head, &QQ[0]);
    printf("%d ", *(int *) list->head->data);
    CListElmt* element = list->head;
    for (int i = 1; i < len(QQ); ++i) {
        clist_ins_next(list, element, &QQ[i]);
        printf("%d ", *(int *) element->next->data);
        element = element->next;
    }
    return 0;
}