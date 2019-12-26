//
// Created by 58252 on 2019/1/31.
//

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "str.h"

bool newString(String str,char *chars)
{ // 生成一个其值等于chars的串T
    int i;
    if(strlen(chars)>MAX_STR_LEN)
        return false;
    else
    {
        for(i=0;i<strlen(chars);i++)
            str[i]=*(chars+i);
        return true;
    }
}

void StrCopy(String T,String S)
{ // 由串S复制得串T
    int i;
    memset(T,0,40);
    while(*T++=*S++);
}

bool StrEmpty(String S)
{ // 若S为空串，则返回true，否则返回false
    if(strlen(S) == 0)
        return true;
    else
        return false;
}

int StrCompare(String S,String T)
{// 初始条件：串S和T存在。操作结果：若S>T，则返回值>0；若S=T，则返回值=0；若S<T，则返回值<0
    for(int i=0;i<strlen(S)&&i<strlen(T);++i){
        if(S[i]!=T[i]){
            return S[i]-T[i];
        }
    }
    return (int) (strlen(S) - strlen(T));
}

int StrLength(String S)
{ // 返回串S的元素个数
    return (int) strlen(S);
}

void ClearString(String S)
{ // 初始条件：串S存在。操作结果：将S清为空串
    memset(S, 0, MAX_STR_LEN+1);
}

bool Concat(String T,String S1,String S2) //
{ // 用T返回S1和S2联接而成的新串。若未截断，则返回true，否则false
    int i;
    if(strlen(S1)+strlen(S2)<=MAX_STR_LEN)
    { // 未截断
        for(i=0;i<strlen(S1);i++){
            T[i]=S1[i];
        }
        for(i=0;i<strlen(S2);i++){
            T[strlen(S1)+i]=S2[i];
        }
        T[strlen(S1) + i] = '\0';
        return true;
    }
    else
    { // 截断S2
        for (i = 0; i < strlen(S1); i++) {
            T[i]=S1[i];
        }
        for (i = 0; i <= MAX_STR_LEN - strlen(S1); i++) {
            T[strlen(S1)+i]=S2[i];
        }
        T[strlen(S1) + i] = '\0';
        return false;
    }
}

bool SubString(String Sub,String S,int pos,int len)
{ // 用Sub返回串S的第pos个字符起长度为len的子串.
    int i;
    if(pos<1||pos>strlen(S)||len<0||len>strlen(S)-pos+1)
        return false;
    for(i=0;i<len-pos+1;i++)
        Sub[i]=S[pos+i];
    Sub[i] = '\0';
    return true;
}

int Index(String S,String T,int pos)
{ // 返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数值为0。
    // 其中，T非空，1≤pos≤StrLength(S)。
    int i,j;
    if(pos>=0&&pos<strlen(S))
    {
        i=pos;
        j=0;
        while(i<strlen(S)&&j<strlen(T)){
            if(S[i]==T[j]) // 继续比较后继字符
            {
                ++i;
                ++j;
            }
            else // 指针后退重新开始匹配
            {
                i=i-j+1;
                j=0;
            }
        }
        if(j==strlen(T))
            return (int) (i - strlen(T));
        else
            return 0;
    }
    else
        return 0;
}

bool StrInsert(String S,int pos,String T)
{ // 初始条件：串S和T存在，1≤pos≤StrLength(S)+1
    // 操作结果：在串S的第pos个字符之前插入串T。完全插入返回true，部分插入返回false
    int i;
    if(strlen(S)+strlen(T)<MAX_STR_LEN)
    { // 完全插入
        int size = (int) strlen(S);
        for(i=size;i>=pos;i--)
            S[i+strlen(T)]=S[i];
        S[strlen(T) + strlen(S)] = '\0';
        for(i=pos;i<pos+strlen(T);i++)
            S[i]=T[i-pos];
        return true;
    } else{
        return false;
    }
}

bool StrDelete(String S,int pos,int len)
{ // 初始条件：串S存在，1≤pos≤StrLength(S)-len+1
    // 操作结果：从串S中删除第pos个字符起长度为len的子串
    int i;
    if(pos<0||pos>strlen(S)-len||len<0)
        return false;
    for(i=pos+len;i<strlen(S);i++)
        S[i-len]=S[i];
    S[strlen(S) - len ] = '\0';
    return true;
}

bool Replace(String S,String T,String V) // 此函数与串的存储结构无关
{ // 初始条件：串S，T和V存在，T是非空串
    // 操作结果：用V替换主串S中出现的所有与T相等的不重叠的子串
    int i=0; // 从串S的第一个字符起查找串T
    bool k;
    if(StrEmpty(T)) // T是空串
        return false;
    do
    {
        i=Index(S,T,i); // 结果i为从上一个i之后找到的子串T的位置
        if(i) // 串S中存在串T
        {
            StrDelete(S,i,StrLength(T)); // 删除该串T
            StrInsert(S,i,V); // 在原串T的位置插入串V
            i+=StrLength(V); // 在插入的串V后面继续查找串T
        }
    }while(i);
    return true;
}