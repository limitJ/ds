#ifndef _SET_H
#define _SET_H 1
#include "list.h"
#include "stdbool.h"
typedef List Set;
void set_init(Set* set1,int (*compare)(const void* key1,const void* key2),void (*destroy)(void* data));
bool in(const Set* set1,const void* data);
bool add(Set* set1,void* data);
bool del(Set* set1,void** data);
bool unions(Set* set3,Set* set1,Set* set2);
bool set_occur(Set* set3,Set* set1,Set* set2);
bool except(Set* set3,Set* set1,Set* set2);
bool isSubSet(const Set* set1,const Set* set2);
bool equals(const Set* set1,const Set* set2);

#endif