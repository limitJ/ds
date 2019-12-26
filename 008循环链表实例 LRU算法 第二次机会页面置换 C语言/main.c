/*QQ: 582521582
 * QQ群: 322085520
 * 循环链表
 * */
#include <stdio.h>
#include "clist.h"
#define len(arr) sizeof(arr)/sizeof(arr[0])
int main() {
    CList *list = (CList *) malloc(sizeof(CList));
    clist_init(list, NULL);
    LRU page[] = {
            {0,1},
            {1,0},
            {2,1},
            {3,1},
            {4,0},
            {5,1}
    };
    clist_ins_next(list, list->head, &page[0]);
    printf("%d ",((LRU*)list->head->data)->number);
    CListElmt *element = list->head;
    for (int i = 1; i < len(page); ++i) {
        clist_ins_next(list, element, &page[i]);
        printf("%d ",((LRU*)element->next->data)->number);
        element = element->next;
    }//初始化添加数据
    int x = rep(&list->head->next->next);
    printf("\n%d\n", x);
    return 0;
}