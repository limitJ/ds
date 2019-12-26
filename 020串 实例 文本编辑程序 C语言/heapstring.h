//
// Created by 58252 on 2019/2/14.
//

#ifndef HEAPSTR_HEAPSTRING_H
#define HEAPSTR_HEAPSTRING_H
//串的堆分配存储
#include <stdbool.h>
typedef struct HeapString
{
    char *ch; // 若是非空串，则按串长分配存储区，否则ch为NULL
    int len; // 串长度
}hstring;
hstring* newhstring(char *chars);
void print(hstring* T);
bool isEmpty(hstring* S);
int compare(hstring* S, hstring* T);
int getLength(hstring* S);
void clearhstring(hstring* S);
void append(hstring* S1, hstring* S2);
hstring* substring(hstring* S,int start,int end);
int indexof(hstring* S, hstring* T, int pos);
bool insert(hstring* S,int pos, hstring* T);
bool delete(hstring* S,int start,int end);
bool replace(hstring* S,hstring* T, hstring* V);
#endif //HEAPSTR_HEAPSTRING_H
