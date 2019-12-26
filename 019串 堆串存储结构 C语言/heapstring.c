//
// Created by 58252 on 2019/2/14.
//
#include "heapstring.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

hstring* newhstring(char* chars)
{ // 生成一个其值等于串常量chars的串
    hstring* heapstr = (hstring*)malloc(sizeof(hstring));
    if (heapstr == NULL) {
        exit(-1);
    }
    int lens = 0;
    lens = (int) strlen(chars); // 求chars的长度i
    if (lens == 0) { // chars的长度为0时候 返回NULL
        return NULL;
    }else { // chars的长度不为0
        heapstr->ch = (char *) malloc(lens * sizeof(char)); // 分配串空间
        if (heapstr->ch == NULL){ // 分配串空间失败
            exit(-1);
        }
        for (int i = 0; i < lens; i++) { // 拷贝串
            heapstr->ch[i] = chars[i];
        }
        heapstr->len = lens;
        return heapstr;
    }
}
void print(hstring* heapStr) { // 输出T字符串。另加
    int i;
    for (i = 0; i < heapStr->len; i++)
        printf("%c", heapStr->ch[i]);
    printf("\n");
}

bool isEmpty(hstring* S) { // 若S为空串，则返回TRUE，否则返回FALSE
    if (S->len == 0 && S->ch == NULL)
        return true;
    else
        return false;
}

int compare(hstring* S, hstring* T) { // 若S>T，则返回值>0；若S=T，则返回值=0；若S<T，则返回值<0
    int i;
    for (i = 0; i < S->len && i < T->len; ++i){
        if (S->ch[i] != T->ch[i]) { //一直相等 一直比较 知道比较到不同的字符的时候 返回!
            return S->ch[i] - T->ch[i];
        }
    }
    return S->len - T->len; //到这里说明前面都是一样的 但是 还没有比完 长度不一样 就直接返回长度差
}

int getLength(hstring* S) { // 返回S的元素个数，称为串的长度
    return S->len;
}

void clearhstring(hstring* S){ // 将S清为空串
    free(S->ch);
    S->ch = NULL;
    S->len = 0;
}

void append(hstring* S1, hstring* S2){ //由s2添加进s1
    int lens = S1->len+S2->len;
    int oldlen = S1->len;
    S1->ch = (char *) realloc(S1->ch,(size_t) lens);
    if (S1->ch == NULL) {
        exit(-1);
    }
    for (int i = 0; i < S2->len; ++i) {
        S1->ch[oldlen + i] = S2->ch[i];
    }
    S1->len = lens;
}

hstring* substring(hstring* S,int start,int end){ // 用Sub返回串S的下标从start - end-1的子串
    int i;
    if (start < 0 || start > S->len || end < 1 || end > S->len || end<=start ) {
        puts("大概是越界了吧!强制退出!");
        exit(-1);
    }
    hstring *Sub = (hstring *) malloc(sizeof(hstring));
    if (Sub == NULL) {
        exit(-1);
    }
    if (S->len == 0 && S->ch == NULL) {
        Sub = NULL;
        return Sub;
    }else{ // 完整子串
        int len = end - start;
        Sub->ch = (char *) malloc(len * sizeof(char));
        if (Sub->ch == NULL) {
            exit(-1);
        }
        for (i = 0;i<len;i++){
            Sub->ch[i] = S->ch[i + start];
        }
        Sub->len = len;
        return Sub;
    }
}

int indexof(hstring* S, hstring* T, int pos){ // T为非空串。若主串S中第pos个字符之后存在与T相等的子串.
    // 则返回第一个这样的子串在S中的位置，否则返回-1
    int n, m;
    if (pos >= 0) {
        n = getLength(S);//22
        m = getLength(T);//4
        while (pos < n - m) {
            hstring* sub = substring(S, pos, pos+m);
            if (compare(sub, T) != 0){
                ++pos;
            }else{
                return pos;
            }
            clearhstring(sub);
            free(sub);
        }
        if (pos == n - m) {
            hstring* sub = substring(S, pos, pos+m);
            if (compare(sub, T) == 0) {
                return pos;
            } else{
                return -1;
            }
        }
    }
    return -1;
}

bool insert(hstring* S,int pos, hstring* T){ //在串S的第下标为pos个字符之前插入串T
    if (pos < 0 || pos > S->len) {
        return false;
    } // pos不合法
     if (T->len != 0) {// T非空，则重新分配空间，插入T
          S->ch = (char *) realloc(S->ch, (S->len + T->len) * sizeof(char)); //realloc会保留原有的数据
         if (S->ch == NULL) {
             exit(-1);
         }
         for (int i = S->len - 1;i>=pos;--i){ // 为插入T而腾出位置
             S->ch[i+T->len]=S->ch[i];
         }
         for (int i = 0;i<T->len;i++){
             S->ch[pos+i]=T->ch[i]; // 插入T
         }
         S->len = S->len + T->len;
    }
    return true;
}

bool delete(hstring* S,int start,int end){ // 从串S中删除
    int i;
    if (start < 0 || start > S->len || end < 1 || end <= start || end>S->len) {
        puts("大概是越界了吧!强制退出!");
        exit(-1);
    }
    if (end == S->len) {
        S->len = S->len - (end - start);
        S->ch = (char *) realloc(S->ch, S->len * sizeof(char));
        return true;
    }
    int len = end - start;
    for (i = start;i<=S->len-len;i++) {
        S->ch[i] = S->ch[i + len];
    }
    S->len = S->len - len;
    S->ch = (char *) realloc(S->ch, S->len * sizeof(char));
    return true;
}

bool replace(hstring* S,hstring* T, hstring* V) { // 用V替换主串S中出现的所有与T相等的不重叠的子串
    //I Love Java And Java
    int i = 0; // 从串S的第一个字符起查找串T
    if (isEmpty(T) == true){
        return false;
    } // T是空串
    do{
        i = indexof(S, T, i); // 结果i为从上一个i之后找到的子串T的位置
        if (i!=-1) {// 串S中存在串T
            delete(S, i, i+getLength(T)); // 删除该串T
            insert(S, i, V); // 在原串T的位置插入串V
            i+=getLength(V); // 在插入的串V后面继续查找串T
        }
    }while (i!=-1);
    return true;
}


