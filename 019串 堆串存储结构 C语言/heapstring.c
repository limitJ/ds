//
// Created by 58252 on 2019/2/14.
//
#include "heapstring.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

hstring* newhstring(char* chars)
{ // ����һ����ֵ���ڴ�����chars�Ĵ�
    hstring* heapstr = (hstring*)malloc(sizeof(hstring));
    if (heapstr == NULL) {
        exit(-1);
    }
    int lens = 0;
    lens = (int) strlen(chars); // ��chars�ĳ���i
    if (lens == 0) { // chars�ĳ���Ϊ0ʱ�� ����NULL
        return NULL;
    }else { // chars�ĳ��Ȳ�Ϊ0
        heapstr->ch = (char *) malloc(lens * sizeof(char)); // ���䴮�ռ�
        if (heapstr->ch == NULL){ // ���䴮�ռ�ʧ��
            exit(-1);
        }
        for (int i = 0; i < lens; i++) { // ������
            heapstr->ch[i] = chars[i];
        }
        heapstr->len = lens;
        return heapstr;
    }
}
void print(hstring* heapStr) { // ���T�ַ��������
    int i;
    for (i = 0; i < heapStr->len; i++)
        printf("%c", heapStr->ch[i]);
    printf("\n");
}

bool isEmpty(hstring* S) { // ��SΪ�մ����򷵻�TRUE�����򷵻�FALSE
    if (S->len == 0 && S->ch == NULL)
        return true;
    else
        return false;
}

int compare(hstring* S, hstring* T) { // ��S>T���򷵻�ֵ>0����S=T���򷵻�ֵ=0����S<T���򷵻�ֵ<0
    int i;
    for (i = 0; i < S->len && i < T->len; ++i){
        if (S->ch[i] != T->ch[i]) { //һֱ��� һֱ�Ƚ� ֪���Ƚϵ���ͬ���ַ���ʱ�� ����!
            return S->ch[i] - T->ch[i];
        }
    }
    return S->len - T->len; //������˵��ǰ�涼��һ���� ���� ��û�б��� ���Ȳ�һ�� ��ֱ�ӷ��س��Ȳ�
}

int getLength(hstring* S) { // ����S��Ԫ�ظ�������Ϊ���ĳ���
    return S->len;
}

void clearhstring(hstring* S){ // ��S��Ϊ�մ�
    free(S->ch);
    S->ch = NULL;
    S->len = 0;
}

void append(hstring* S1, hstring* S2){ //��s2��ӽ�s1
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

hstring* substring(hstring* S,int start,int end){ // ��Sub���ش�S���±��start - end-1���Ӵ�
    int i;
    if (start < 0 || start > S->len || end < 1 || end > S->len || end<=start ) {
        puts("�����Խ���˰�!ǿ���˳�!");
        exit(-1);
    }
    hstring *Sub = (hstring *) malloc(sizeof(hstring));
    if (Sub == NULL) {
        exit(-1);
    }
    if (S->len == 0 && S->ch == NULL) {
        Sub = NULL;
        return Sub;
    }else{ // �����Ӵ�
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

int indexof(hstring* S, hstring* T, int pos){ // TΪ�ǿմ���������S�е�pos���ַ�֮�������T��ȵ��Ӵ�.
    // �򷵻ص�һ���������Ӵ���S�е�λ�ã����򷵻�-1
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

bool insert(hstring* S,int pos, hstring* T){ //�ڴ�S�ĵ��±�Ϊpos���ַ�֮ǰ���봮T
    if (pos < 0 || pos > S->len) {
        return false;
    } // pos���Ϸ�
     if (T->len != 0) {// T�ǿգ������·���ռ䣬����T
          S->ch = (char *) realloc(S->ch, (S->len + T->len) * sizeof(char)); //realloc�ᱣ��ԭ�е�����
         if (S->ch == NULL) {
             exit(-1);
         }
         for (int i = S->len - 1;i>=pos;--i){ // Ϊ����T���ڳ�λ��
             S->ch[i+T->len]=S->ch[i];
         }
         for (int i = 0;i<T->len;i++){
             S->ch[pos+i]=T->ch[i]; // ����T
         }
         S->len = S->len + T->len;
    }
    return true;
}

bool delete(hstring* S,int start,int end){ // �Ӵ�S��ɾ��
    int i;
    if (start < 0 || start > S->len || end < 1 || end <= start || end>S->len) {
        puts("�����Խ���˰�!ǿ���˳�!");
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

bool replace(hstring* S,hstring* T, hstring* V) { // ��V�滻����S�г��ֵ�������T��ȵĲ��ص����Ӵ�
    //I Love Java And Java
    int i = 0; // �Ӵ�S�ĵ�һ���ַ�����Ҵ�T
    if (isEmpty(T) == true){
        return false;
    } // T�ǿմ�
    do{
        i = indexof(S, T, i); // ���iΪ����һ��i֮���ҵ����Ӵ�T��λ��
        if (i!=-1) {// ��S�д��ڴ�T
            delete(S, i, i+getLength(T)); // ɾ���ô�T
            insert(S, i, V); // ��ԭ��T��λ�ò��봮V
            i+=getLength(V); // �ڲ���Ĵ�V����������Ҵ�T
        }
    }while (i!=-1);
    return true;
}


