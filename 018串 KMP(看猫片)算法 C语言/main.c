/*****QQ: 582521582
 * ***QQ群: 322085520
     * KMP的关键在于
     * 1：为什么移动和主串没关系 反而和模式串有关系
     * 2：如何求最大后缀
     * 3：为什么可以根据后缀所指下标移动
     * 第一个问题 （abcdabca的后缀表达式为 -1 0 0 0 0 1 2 3）
     * a b c d d a b c d a b c b a b c d a b c a b c
     *           a b c d a b c a  //可以移动3这个位置 说明必有前缀abc和后缀abc相等 而前面不可能再出现其他的abc
     *          -1 0 0 0 0 1 2 3
     * 第一次比较 移动后变成
     * 为什么 可以直接移动
     *这个例子不是很明显 让我们举个比较明显的例子
     * a b a b d a a b a b d b
     * a b a b d b
     *-1 0 0 1 2 0
     * 移动后
     * a b a b d a a b a b d b
     *           a b a b d b
     *          -1 0 0 1 2 0
     * 如果稍作改动 主串中的第5个d改成a
     * a b a b a a b a b d b
     * a b a b d b
     *-1 0 0 1 2 0
     * 移动后
     * a b a b a a b a b d b
     *     a b a b d b
     *    -1 0 1 2 0 0
     * 可以看出只是改动一个 移动的差别就显示出来
     * 根据后缀来判断有没有必要比较前面的
     * 改动前 比较主串a与模式串b不匹配 需要移动 而模式串中的b指向的是0这个坐标 说明模式串中的b之前的字符串 没有最大后缀
     * 但是既然比到了b这个位置 说明 主串前面的字符 和模式串 比到部分的前面的字串是完全相等的
     * 这就说明既然d是0 主串中 不可能出现另一个abd 所以阔以直接移动
     * 然后就是改动后的
     * 比到a != d的时候 指向2 说明模式串a b a b需要将a移动到与比较不同的主串中的a对齐
     * 除了后缀的ab 中间不会出现ab可以使ab对齐 所以前面的数也不要比较了！
     * 第二个问题 如何求最大后缀 见函数suffix注释
     *
     */
#include <stdio.h>
#include <string.h>
void suffix(const char* pattern,int plen,int* next);
int KMP(const char* str,int slen ,const char* pattern,int plen);
int main(void) {
    char str[] = "abcddabcdabcbabcdabcabc";
    char pattern[] = "bcdabcb";
    int index = KMP(str, (int) strlen(str), pattern, (int) strlen(pattern));
    printf("%d\n",index);
    return 0;
}
int KMP(const char* str,int slen ,const char* pattern,int plen){
    int next[plen];
    suffix(pattern, plen, next);
    int i = 0,j = 0;
    while (i < slen && j < plen) {
        if(j == -1 || str[i] == pattern[j]){
            i++;
            j++;
        }else{
            j = next[j];
        }
    }
    if (j == plen) {
        return i - j;
    }else{
        return -1;
    }
}
void suffix(const char* pattern,int plen,int* next){
    next[0] = -1;
    for (int i = 1; i < plen; ++i) {
        next[i] = 0; //初始化next表 第一个元素 第二个元素恒为 -1 0 其他元素初始化0
    }
    for (int i = 2; i < plen; ++i) { //从第3个元素 下标2开始
        while (1) {
            if(pattern[next[i-1]] == pattern[i - 1]){  //last在next中表示上一个数比较到哪里没有重复 然后和下面的数开始比较
                next[i] = next[i-1]+1;                 //如果比较相等 则说明前面的数 加上比较的数 完全相等 则在next[i-1]的基础上+1
                break;
             }else{
                next[i] = 0; //不相等 则跳出循环 另一方面是将下次相比较的数 可以从pattern[]再次开始比较
                break;
            }

        }
    }
}