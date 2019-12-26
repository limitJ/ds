//
// Created by 58252 on 2019/2/14.
//

#ifndef HEAPSTR_HEAPSTRING_H
#define HEAPSTR_HEAPSTRING_H
//���Ķѷ���洢
#include <stdbool.h>
typedef struct HeapString
{
    char *ch; // ���Ƿǿմ����򰴴�������洢��������chΪNULL
    int len; // ������
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
