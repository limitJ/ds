/*
 * QQ:   582521582
 * QQ群: 322085520
 *串 针对string的基本操作
 * */
#include <stdio.h>
#include <mem.h>
#include "str.h"
#define boolean(flag) flag?"true":"false"
#define compare(com) com>0?("c1>c2"):(com<0?"c1<c2":"c1=c2")
int main() {
    String strs;
    newString(strs, "1234556");//生成一个字符串
    puts(strs);
    StrCopy(strs, "79");//拷贝字符串
    puts(strs);
    StrCopy(strs, "");//拷贝字符串
    bool flag = StrEmpty(strs);
    printf("%s\n", boolean(flag));
    int com = StrCompare("a", "b");
    printf("%s\n", compare(com));
    StrCopy(strs, "123546");
    ClearString(strs);
    StrCopy(strs, "1234567");
    puts(strs);
    String str2;
    Concat(str2, strs, "89");
    puts(str2);
    String str3;
    SubString(str3,str2,2,5); //生成子串
    puts(str3);
    String str4;
    StrCopy(str4,"JavaWoaiJavaLLoveYou");//查询子串出现的位置
    int index = Index(str4, "Love", 1);
    printf("%d\n", index);
    String str5;
    newString(str5, "Java");
    StrInsert(str5,1,"qaq");//插入新子串
    puts(str5);
    String str6;
    newString(str6, "javac");
    StrDelete(str6,2,2);//删除子串
    puts(str6);
    String str7;
    newString(str7,"L Love Python And Python");//替换子串
    Replace(str7,"Python","Java");
    puts(str7);
    return 0;
}