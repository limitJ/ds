/*
 * 数据结构
 * KMP的一种改进的算法
 * next优化成nextval的算法
 * 例子 传统的p串的next = {-1,0,0,0,1,2,3}
 * abcabdabcabcd
 * abcabcd
 *    abcabcd
 *    可以看到p串前后都有abc这个串 但是 前面的abc和主串abd已经比较过一次
 *    而p串后面与p串前面相等的abc又重复和主串的abd又比较了一次
 *    所以这是没有必要的 因此有了对kmp的改进算法 其实就是改进next 让next滑动的更加的远
 *    nextval = {-1,0,0,-1,0,0,3}
 *    nextval[3] = -1 是因为 当此位置发生适配 因为这个位置p串a = a 没有必要比较多余一次 直接跳过
 *    nextval[4] = 0 ab = ab同理
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
            i++;
            j++;
        } else{
            j = nextval[j];
        }
    }
    return j == strlen(pattern) ? i - j : -1;

}

int *suffixval(char *pattern) {
    int *nextval = (int *) malloc(sizeof(int) * strlen(pattern));
    memset(nextval, 0, sizeof(int) * strlen(pattern));
    nextval[0] = -1;
    int i = 0, j = -1;
    //常规next函数求法
//    for (int i = 2; i < strlen(pattern); ++i) {
//        nextval[i] = pattern[nextval[i - 1]] == pattern[i - 1] ? nextval[i - 1] + 1 : 0;
//    }

//  改进后的nextval求法
    while (i < strlen(pattern) - 1) {
        if (j == -1 || pattern[i] == pattern[j]) {
            i++;
            j++;
            if (pattern[i] == pattern[j]) {
                nextval[i] = nextval[j];
            } else {
                nextval[i] = j;
            }
        } else {
            j = nextval[j];
        }
    }
    return nextval;
}