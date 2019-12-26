#include <stdio.h>
#include "list.h"
void destroy(void* data)
{
    free(data);
}

int compare(const void* key1, const void* key2)
{
    return *(int*)key1 - *(int*)key2;
}
int main(void) {
    int data[]={5,8,2,5,2,1,5,8,2};
    List *list = new(List);
    init_list(list, &destroy);
    for (int i = 0; i < len(data); ++i) {
        //每次在队尾插入 相当于队列 如果是插入NULL 则每次在队头插入 相当于栈
        insert(list,list->tail,createNode(&data[i]));
        printf("%d ",*(int*)list->head->data);//输出队头 如果是每次插在队尾 可以输出队尾的data
    }
    printf("\nelement = %d index = %d\n",*(int*)(find(list, &data[5], &compare)->data),getLoc(list,find(list, &data[5], &compare)));
    ListElement* e;
    while((e = delete(list,NULL))!=NULL)
    {
        printf("%d ",*(int*)e->data);
    }

    printf("\nisEmpty? %s\n",boolean(isEmpty(list)));
    list_destroy(list);
    printf("Done!");
    return 0;
}