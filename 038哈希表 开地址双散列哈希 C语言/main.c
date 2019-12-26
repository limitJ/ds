#include <stdio.h>
#include "ohashmap.h"
int hashcode1(const void* key);
int hashcode2(const void* key);
int compare(const void* key1,const void* key2);
int main(void) {
    //双散列哈希
    OHashMap *oHashMap = (OHashMap *) malloc(sizeof(OHashMap));
    init_ohashmap(oHashMap, 10, hashcode1, hashcode2, compare, NULL);
    int data[8]={
            78,14,37,83,97,59,25,72
    };

    for (int i = 0; i < 8; ++i) {
        insert(oHashMap, &data[i]);
    }
    for (int i = 0; i < oHashMap->positions; ++i) {
        if (oHashMap->map[i] != NULL) {
            printf("%d %d\n", i, *(int *) oHashMap->map[i]);
        }
    }
    return 0;
}
int hashcode1(const void* key){
    int val = *(int*)key;
    int temp = 0;
    val = (val<<4)+val;
    if((temp = (val & 0XF0000000))){
        val = val^(temp>>24);
        val = val^temp;
    }
    return val;
}

int hashcode2(const void* key){
    int val = *(int*)key;
    int temp = 0;
    val = (val<<5)+val;
    if((temp = (val & 0XF0000000))){
        val = val^(temp>>24);
        val = val^temp;
    }
    return val;
}

int compare(const void* key1,const void* key2){
    return *(int*)key1 - *(int*)key2;
}