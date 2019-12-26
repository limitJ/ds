/*
 *单链表
 * */
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>
#define len(arr) sizeof(arr)/sizeof(arr[0])
typedef struct ListElmts{
    void* data;
    struct ListElmts* next;
}ListElmt;
typedef struct Lists{
    int size;
    int (*match)(const void* key1,const void* key2);
    void (*destroy)(void* data);
    ListElmt * head;
    ListElmt* tail;
}List;
void destroy(void* data);
void list_destroy(List* list);
void list_init(List* list,void (*destroy)(void* data));//初始化链表
bool list_rem_next(List* list,ListElmt* element,void** data);
bool list_ins_next(List* list,ListElmt* element,const void* data);
int main() {
    List* list = (List *) malloc(sizeof(List));
    list_init(list,&destroy);
    int QQ[9] = { //存放9个链表数据
            [0] = 2,[1] = 8,[2] = 5,
            [3] = 1,[4] = 2,[5] = 5,
            [6] = 2,[7] = 8,[8] = 5,
    };
    for (int i = 0; i < len(QQ); ++i) {
        list_ins_next(list, NULL, &QQ[i]);//当elmement为NULL的时候 则插入头部 否则是指定在某个element后面插入一个新元素
    }
    ListElmt* element = list->head;
    while (element!= NULL) {              //这种头插法 在头部数据域是存放数据的
        printf("%d ", *(int*)element->data);//添加按顺序添加 输出顺序是逆序的 有点像数据结构 栈
        element = element->next;
    }
    printf("\n");
    ListElmt* element2 = list->head;
    ListElmt* e = list->head->next;    //删除元素8这个节点
    list_rem_next(list, e, &e->data);  //注意传地址
    while (element2!= NULL) {              //这种头插法 在头部数据域是存放数据的
        printf("%d ", *(int*)element2->data);//添加按顺序添加 输出顺序是逆序的 有点像数据结构 栈
        element2 = element2->next;
    }
    list_destroy(list);//销毁整个链表
    printf("\n%d\n", list->size);
    return 0;
}
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
        old_element = list->head;//当不指定移除具体项的时候 依次从头部开始移除
        list->head = list->head->next;
        if (list->size == 1) {
            list->tail = NULL;
        }
    }else{
        if (element->next == NULL) {
            return false;
        }
        *data = element->next->data;
        old_element = element->next;   //移除指定元素 并保存下来 以便于调用free释放节点
        element->next = old_element->next;//指向下一个元素的下一个元素
        if (element->next == NULL) {
            list->tail = element;
        }
    }
    free(old_element);
    list->size--;
    return true;
}

void list_init(List* list,void (*destroy)(void* data)){//初始化链表
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}
void list_destroy(List* list){//销毁链表
    while (list->size > 0) {
        if (list_rem_next(list, NULL, &list->head->data) == 0 && list->destroy != NULL) {
            list->destroy(&list->head->data); //如果初始化链表的时候destroy参数不为NULL则销毁链表的时候每次调用都会销毁数据
        }
    }
    memset(list, 0, sizeof(List));//将List指向的内存初始化 全部填充0
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
        new_element->next = list->head;  //如果没有传入element节点 则尾插法在头部添加数据
        list->head = new_element;        //链表头存放了数据也存放了指针域
    }else{
        if (element->next == NULL) {     //在指定element后插入一条新数据
            list->tail = new_element;    //如果尾部 则将tail值为NULL
        }
        new_element->next = element->next;
        element->next = new_element;
    }
    list->size++;
    return true;
}