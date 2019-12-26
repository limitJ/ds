//
// Created by QQ 582521582 on 2019/4/17.
//
#include "list.h"
void init_list(List* list,void (*destroy)(void*))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}
void list_destroy(List* list)
{
    while(list->size!=0)
    {
        ListElement* old_element = delete(list,NULL);
        assert(old_element!=NULL);
        if (list->destroy != NULL) {
            list->destroy(old_element->data);
        }
        dispose(old_element);
    }
    memset(list, 0, sizeof(List));
    free(list);
}
ListElement* createNode(const void* data)
{
    ListElement *new_element = new(ListElement);
    if (new_element == NULL)
    {
        throwException("create element failed!\n");
        return false;
    }
    new_element->data = (void*)data;
    return new_element;
}
//第二个参数3种取值 1：NULL:就相当于栈 2：list->tail：就相当于 队列 3：其他位置插入 单链表
bool insert(List* list,ListElement* element,ListElement* new_element)
{
    if (new_element == NULL)
    {
        throwException("create element failed!\n");
        return false;
    }
    if (element == NULL)//头插法链表 具有后进先出的栈存储结构
    {
        if (list->size == 0)
        {
            list->tail = new_element;
        }
        new_element->next = list->head;
        list->head = new_element;
    }
    else
    {
        assert(list->head != NULL);
        if (element->next == NULL)
        {
            list->tail = new_element;//插入insert(list,list->tail,data)一直插入队尾 是队列存储结构
        }
        new_element->next = element->next;
        element->next = new_element;
    }
    ++list->size;
    return true;
}

ListElement* delete(List* list,ListElement* element)//删除节点的后一个元素
{
    ListElement *old_element = NULL;
    if (0 == list->size)
    {
        return NULL;
    }
    if (element == NULL)
    {
        old_element = list->head;
        list->head = list->head->next;
        if(list->size == 1)
        {
            list->tail = NULL;
        }
    }
    else
    {
        assert(list->head != NULL);
        if (element->next == NULL)
        {
            throwException("delete failed,listElement is non-existent!\n");
            return NULL;
        }
        old_element = element->next;
        element->next = old_element->next;
        if (element->next == NULL)
        {
            list->tail = element;
        }
    }
    list->size--;
    return old_element;
}
void dispose(ListElement* element)
{
    free(element);
}

ListElement* find(List* list, const void* data,int (*compare)(const void* , const void*))
{
    ListElement* member;
    list->compare = compare;
    for(member = list->head;member!=NULL;member = member->next)
    {
        if (list->compare(data,member->data)==0)
        {
            break;
        }
    }
    if (member == NULL)
    {
        return NULL;
    }
    return member;
}

int getLoc(List* list,ListElement* element)
{
    assert(list != NULL && list->size != 0);
    ListElement* member = NULL;
    int loc = 0;
    for(member = list->head;member!=NULL;member=member->next)
    {
        if (memcmp(element, member, sizeof(ListElement)) == 0) {
            break;
        }
        loc++;
    }
    return loc;
}

bool isEmpty(List* list)
{
    return 0 == list->size;
}