/*
 * 数据结构
 * 通用 双链表 栈 队列
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "list.h"
#define len(arr) (int)(sizeof(arr)/sizeof(typeof(arr[0])))
typedef struct HashMap{
    int key;
    void* value;
}HashMap;
void destroy(void* data);
void visit(void* data);

typedef List Stack;
typedef List Queue;
int main(void) {
    HashMap student[3] ={
           [0]={
                   .key = 1,
                   .value = "小明"
           },
           [1] = {
                   .key = 2,
                   .value = "小红"
           },
           [2]  = {
                   .key = 3,
                   .value = "小王"
           }
    };
    printf("------1：头插法链表 栈！--------\n");
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    list_init(stack,&destroy);
    //这是头插法
    printf("每次从头节点插入\n");
    for (int i = 0; i < len(student); ++i) {
        //插入位置是头节点前面list->head==NULL?NULL:list->head->prev
        insert(stack,stack->head==NULL?NULL:stack->head->prev,&student[i]);
        visit(stack->head->data);
    }
    printf("头插法删除元素\n");
    //头插法插入后删除 就是栈
    while (!isEmpty(stack)) {
        HashMap** stu;
        delete(stack, stack->head, (void **) &stu);
        visit(stu);
    }
    list_destroy(stack);


    printf("\n------2：尾插法链表 队列！--------\n");
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    list_init(queue,&destroy);
    //这是尾插法
    printf("每次从尾节点插入\n");
    for (int i = 0; i < len(student); ++i) {
        //这里插入位置list->tail
        insert(queue,queue->tail,&student[i]);
        visit(queue->tail->data);
    }
//    HashMap s = {2,"这是链表中途插入的"};
//    insert(list,list->head->next,&s);
    printf("尾插法删除元素 出队\n");
    //尾插法插入后删除 就是队列
    while (!isEmpty(queue)) {
        HashMap** stu;
        delete(queue, queue->head, (void **) &stu);
        visit(stu);
    }
    list_destroy(queue);

    printf("\n------3：普通的链表形式！--------\n");
    List* list = (List *) malloc(sizeof(List));
    list_init(list,&destroy);
    for (int i = 0; i < len(student); ++i) {
        insert(list,list->head==NULL?NULL:list->head->prev,&student[i]);
    }
    printf("随意插入\n");//注意不要越界
    HashMap s1 = {11,"s1"};
    HashMap s2 = {22,"s2"};
    HashMap s3 = {33,"s3"};
    insert(list,list->head->next,&s1);
    insert(list,list->tail->prev,&s2);
    insert(list,list->head,&s3);
    for (ListElement* element=list->head;element!=NULL;element=element->next) {
        visit(element->data);
    }
    //list_destroy(list);
    printf("随意删除\n");
    HashMap** stu;
    delete(list,  list->head->next, (void **) &stu);
    visit(stu);
    delete(list,  list->head->next->next, (void **) &stu);
    visit(stu);
    delete(list,  list->tail, (void **) &stu);
    visit(stu);
    delete(list,  list->tail->prev, (void **) &stu);
    visit(stu);
    delete(list,  list->head->next, (void **) &stu);
    visit(stu);
    delete(list,  list->tail, (void **) &stu);
    visit(stu);

    list_destroy(list);
    printf("Done!程序结束\n");
    return 0;
}

//用户自定义销毁方法
void destroy(void* data){
    HashMap* map = (HashMap*)data;
    map->key = 0;
    map->value = NULL;
}

void visit(void* data){
    HashMap* map = (HashMap*)data;
    printf("%d ", (*(HashMap *) map).key);
    printf("%s\n", (char*)(*(HashMap *) map).value);
}