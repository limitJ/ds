/*
 * 数据结构
 * KMP 中nextval的另一种求法 根据next求
 * 1:当j = 0时 nextval[j] = -1
 * 2:如果 pattern[j]!=pattern[next[j]] 则 nextval[j] = next[j]
 * 3:如果 pattern[j] == pattern[next[j]] 则nextval[j] = nextval[next[j]]
 * QQ 582521582
 * QQ群 322085520
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int KMP(char* str, char* pattern);
int* suffixval(char* pattern);
int main(void) {
    int index = KMP("abcabdabcabcd", "abcabcd");
    printf("%d\n", index);
    return 0;
}
int KMP(char* str, char* pattern){
    int *nextval = suffixval(pattern);
    int i = 0, j = 0,slen = strlen(str),plen = strlen(pattern);
    while (i < slen && j < plen) {
        if (j == -1 || str[i] == pattern[j]) {
            i++,j++;
        } else{
            j = nextval[j];
        }
    }
    free(nextval);
    return j == strlen(pattern) ? i - j : -1;

}

int *suffixval(char *pattern) {
    int *next = (int *) malloc(sizeof(int) * strlen(pattern));
    int *nextval = (int *) malloc(sizeof(int) * strlen(pattern));
    memset(next, 0, sizeof(int) * strlen(pattern));
    memset(nextval, 0, sizeof(int) * strlen(pattern));
    next[0] = -1,nextval[0] = -1;
    for (int i = 2; i < strlen(pattern); ++i) {
        next[i] = pattern[next[i - 1]] == pattern[i - 1] ? next[i - 1] + 1 : 0;
        nextval[i] = pattern[i] != pattern[next[i]]?next[i]:nextval[next[i]];
    }
    free(next);
    return nextval;
}