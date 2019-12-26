#include <stdio.h>
#include "dlist.h"
#define len(arr) sizeof(arr)/sizeof(arr[0])
int main() {
    DList* list = (DList *) malloc(sizeof(DList));
    dlist_init(list, &destroy);
    int QQ[9]={
            5,8,2,5,2,1,5,8,2
    };
//    for (int i = 0; i < len(QQ); ++i) {
//        dlist_ins_next(list,list->head,&QQ[i]);
//        printf("%d ", *(int *) list->head->data);
//    }
    dlist_ins_next(list,list->head,&QQ[0]);
    printf("%d ", *(int *) list->head->data);
    DListElmt *element = list->head;
    for (int i = 1; i < len(QQ); ++i) {
        dlist_ins_next(list,element,&QQ[i]);
        printf("%d ", *(int *)element->next->data);
        element = element->next;
    }
    dlist_destroy(list);
    dlist_init(list, &destroy);
    free(list);
    printf("\n");
//    DListElmt *element2 = list->head; //bug== 内存泄漏==
//    for (int i = 1; i < len(QQ); ++i) {
//        dlist_ins_last(list, element2, &QQ[i]);
//        printf("%d ", *(int *)element2->next->data);
//    }
    return 0;
}