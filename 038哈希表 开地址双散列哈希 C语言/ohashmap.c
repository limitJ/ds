//
// Created by QQ 582521582 on 2019/4/19.
//
#include "ohashmap.h"
static char vacated;
bool init_ohashmap(
        OHashMap* oHashMap,
        int positions,
        int (*hashcode1)(const void*),
        int (*hashcode2)(const void*),
        int (*compare)(const void*,const void*),
        void (*destroy)(void*)
)
{
    oHashMap->map = (void**)malloc(positions* sizeof(void*));
    if (oHashMap->map == NULL) {
        return false;
    }
    oHashMap->positions = positions;
    for (int i = 0; i < oHashMap->positions; ++i) {
        oHashMap->map[i] = NULL;
    }
    oHashMap->size = 0;
    oHashMap->hashcode1 = hashcode1;
    oHashMap->hashcode2 = hashcode2;
    oHashMap->compare = compare;
    oHashMap->destroy = destroy;
    return true;
}
void destroy(OHashMap* oHashMap)
{
    if (oHashMap->destroy != NULL) {
        for (int i = 0; i < oHashMap->positions; ++i) {
            if (oHashMap->map[i] != NULL && oHashMap->map[i] != oHashMap->vacated) {
                oHashMap->destroy(oHashMap->map[i]);
            }
        }
    }
    free(oHashMap->map);
    memset(oHashMap,0, sizeof(OHashMap));
}
bool insert(OHashMap* oHashMap, const void* data)
{
    void* tmp;
    int loc;
    if (oHashMap->size == oHashMap->positions) {
        return false;//空间已经满了 不能再存
    }
    tmp = (void*)data;
    if (in(oHashMap,&tmp)) {
        return false;//key已经存在了
    }
    for (int i = 0; i < oHashMap->positions; ++i) {
        loc = (oHashMap->hashcode1(data)+(i*oHashMap->hashcode2(data)))%oHashMap->positions;
        if (oHashMap->map[loc] == NULL || oHashMap->map[loc] == oHashMap->vacated) {
            oHashMap->map[loc] = (void*)data;
            oHashMap->size++;
            return true;
        }
    }
    return false;

}
bool delete(OHashMap* oHashMap,void** data)
{
    int loc;
    for (int i = 0; i < oHashMap->positions; ++i) {
        loc = (oHashMap->hashcode1(data)+(i*oHashMap->hashcode2(data)))%oHashMap->positions;
        if (oHashMap->map[loc] == NULL){
            return false;
        } else if(oHashMap->map[loc] == oHashMap->vacated){
            continue;
        } else if (oHashMap->compare(oHashMap->map[loc], *data)) {
            *data = oHashMap->map[loc];
            oHashMap->map[loc] = oHashMap->vacated;
            oHashMap->size--;
            return true;
        }
    }
    return false;
}
int in(const OHashMap* oHashMap,void** data)
{
    int loc;
    for (int i = 0; i < oHashMap->positions; ++i) {
        loc = (oHashMap->hashcode1(data)+(i*oHashMap->hashcode2(data)))%oHashMap->positions;
        if (oHashMap->map[loc] == NULL){
            return false;
        } else if (oHashMap->compare(oHashMap->map[loc], *data)) {
            return true;
        }
    }
    return false;
}