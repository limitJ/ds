//
// Created by QQ 582521582 on 2019/4/19.
//
#include "list.h"
#include "hashmap.h"
int hashcode(void* key)
{
    //举例一个key是一个字符串 求出hashcode的值
    char* ptr = (char*)key;
    int val = 0;
    while (*ptr)
    {
        int tmp;
        val = (val<<4)+(*ptr);
        if ((tmp = (val&0Xf0000000)){
            val = val^(tmp>>24);
            val = val^tmp;
        }
    }
    return val;
}
bool init_hashmap(
        HashMap* hashMap,
        int buckets,
        int (*hashcode)(const void* key),
        int (*compare)(const void* key1, const void* key2),
        void (*destroy)(void* data)
        )
{
    hashMap->map = (List*)malloc(buckets*sizeof(List));
    if (hashMap->map == NULL) {
        throwException("failed!\n");
        return false;
    }
    hashMap->buckets = buckets;
    for (int i = 0; i < hashMap->buckets; ++i) {
        init_list(&hashMap->map[i], destroy);
    }
    hashMap->hashcode = hashcode;
    hashMap->compare = compare;
    hashMap->destroy = destroy;
    hashMap->size = 0;
}

void destroy_hashmap(HashMap* hashMap)
{
    for (int i = 0; i < hashMap->buckets; ++i) {
        list_destroy(&hashMap->map[i]);
    }
    free(hashMap->map);
}

bool ins(HashMap* hashMap, ListElement* data)
{
    ListElement* tmp;
    int loc = 0;
    int retval = 0;
    tmp = data;
    if (in(hashMap,tmp)){
        return false;
    }
    loc = hashMap->hashcode(data)%hashMap->buckets;
    retval = insert(&hashMap->map[loc],NULL,data);
    if (retval == true)
    {
        hashMap->size++;
    }
    return retval;

}
bool rem(HashMap* hashMap,void** data)
{
    ListElement* element;
    ListElement* prev = NULL;
    int loc;
    loc = hashMap->hashcode(data)%hashMap->buckets;
    for(element = hashMap->map[loc].head;element!=NULL;element = element->next){
        if(hashMap->compare(*data,element->data)!=0){
            ListElement* e = delete(&hashMap->map[loc],NULL);
            if(e!=NULL)
            {
                hashMap->size--;
                return true;
            }
            else
            {
                return false;
            }
        }
        prev = element;
    }
    return  false;
}
bool in(const HashMap* hashMap,ListElement* data)
{
    ListElement* element ;
    int loc;
    loc = hashMap->hashcode(data)%hashMap->buckets;
    for(element = hashMap->map[loc].head;element!=NULL;element = element->next){
        if (hashMap->compare(data,element->data)){
            data = element;
            return true;
        }
    }
    return false;
}