//
// Created by 58252 on 2019/1/31.
//

#ifndef STRING_STRING_H
#define STRING_STRING_H

#include <stdbool.h>
#define MAX_STR_LEN 40 // 用户可在255(1个字节)以内定义最大串长
typedef char String[MAX_STR_LEN+1]; // 0号单元存放串的长度
bool newString(String T,char *chars);
void StrCopy(String T,String S);
bool StrEmpty(String S);
int StrCompare(String S,String T);
void ClearString(String S);
bool Concat(String T,String S1,String S2);
bool SubString(String Sub,String S,int pos,int len);
int Index(String S,String T,int pos);
bool StrInsert(String S,int pos,String T);
bool StrDelete(String S,int pos,int len);
bool Replace(String S,String T,String V);
#endif //STRING_STRING_H
