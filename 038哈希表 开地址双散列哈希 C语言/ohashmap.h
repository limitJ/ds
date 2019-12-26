//
// Created by QQ 582521582 on 2019/4/19.
//

#ifndef OHASHMAP_OHASHMAP_H
#define OHASHMAP_OHASHMAP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
typedef struct OHashMap{
    int positions;
    void *vacated;
    int size;
    void **map;
    int (*hashcode1)(const void* key);
    int (*hashcode2)(const void* key);
    int (*compare)(const void* key1,const void* key2);
    void (*destroy)(void* data);
}OHashMap;
bool init_ohashmap(
        OHashMap* oHashMap,
        int positions,
        int (*hashcode1)(const void* key),
        int (*hashcode2)(const void* key),
        int (*compare)(const void* key1,const void* key2),
        void (*destroy)(void* data)
        );
void destroy(OHashMap* oHashMap);
bool insert(OHashMap* oHashMap, const void* data);
bool delete(OHashMap* oHashMap,void** data);
int in(const OHashMap* oHashMap,void** data);
#endif //OHASHMAP_OHASHMAP_H
