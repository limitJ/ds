#include "set.h"
void initSet(Set* set1,int(*match)(const void* key1,const void* key2),void(*destroy)(void* data))
{
    list_init(set1,destroy);
    set1->match = match;//因为使用的是泛型 所以match函数由使用者自己定义
}

bool add(Set* set1,void* data)
{
    if(in(set1,data))
    {
        return false;
    }
    return list_ins_next(set1,set1->tail,data);
}
bool del(Set* set1,void** data)
{
    ListElmt* element ;
    ListElmt* prev = NULL;
    for(element = set1->head;element!=NULL;element = element->next)
    {
        if(set1->match(*data,element->data)){
            break;
        }
        prev = element;
    }
    if(element==NULL)
    {
        return false;
    }
    return list_rem_next(set1,prev,data);
}

bool unions(Set* set3,Set* set1,Set* set2)
{
    ListElmt* element;
    initSet(set3,set1->match,NULL);
    for(element = set1->head;element!=NULL;element = element->next)
    {
        if(list_ins_next(set3,set3->tail,element->data)!=true)
        {
            destroy(set3);
            return false;
        }
    }

    for(element = set2->head;element!=NULL;element = element->next)
    {
        if(in(set1,element->data))
        {
            continue;
        }
        else
        {
            if(list_ins_next(set3,set3->tail,element->data)!=true)
            {
                destroy(set3);
                return false;
            }
        }
    }
    return true;
}

bool occur(Set* set3,Set* set1,Set* set2)
{
    ListElmt* element;
    initSet(set3,set1->match,NULL);
    for(element = set1->head;element!=NULL;element=element->next)
    {
        if(in(set2,element->data))
        {
            if(list_ins_next(set3,set3->tail,element->data)!=true)
            {
                destroy(set3);
                return false;
            }
        }
    }
    return false;
}

bool except(Set* set3,Set* set1,Set* set2)
{
     ListElmt* element;
     initSet(set3,set1->match,NULL);
    for(element = set1->head;element!=NULL;element=element->next)
    {
        if(!in(set2,element->data))
        {
            if(list_ins_next(set3,set3->tail,element->data)!=true)
            {
                destroy(set3);
                return false;
            }
        }
    }
    return true;
}

bool isSubSet(const Set* set1,const Set* set2)
{
    ListElmt* element;
    if(set1->size>set2->size)
    {
         return false;
    }
    for(element=set1->head;element!=NULL;element = element->next)
    {
        if(!in(set2,element->data))
        {
            return false;
        }
    }
    return true;
}

bool equals(const Set* set1,const Set* set2)
{
    if(set1->size!=set2->size)
    {
        return false;
    }
    return isSubSet(set1,set2);
}

bool in(const Set* set1,const void* data)
{
    ListElmt* element ;
    for(element=set1->head;element!=NULL;element = element->next)
    {
        if(set1->match(data,element->data)){
            return true;
        }
    }
    return false;
}
