//
// Created by QQ 582521582 on 2019/4/19.
//

#ifndef HASHMAP_HASHMAP_H
#define HASHMAP_HASHMAP_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
typedef struct HashMap{
    int buckets;//哈希表分配桶的个数
    int size;
    List* map;
    int (*hashcode)(const void* key);//计算散列值函数
    int (*compare)(const void* key1, const void* key2);
    void (*destroy)(void* data);
}HashMap;
bool init_hashmap(
        HashMap* hashMap,
        int buckets,
        int (*hashcode)(const void* key),
        int (*compare)(const void* key1, const void* key2),
        void (*destroy)(void* data)
        );
void destroy_hashmap(HashMap* hashMap);
bool ins(HashMap* hashMap, ListElement* data);
bool rem(HashMap* hashMap,void** data);
bool in(const HashMap* hashMap,ListElement* data);//查看元素是否在hashmap中
#endif //HASHMAP_HASHMAP_H
