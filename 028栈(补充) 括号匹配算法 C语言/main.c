#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
bool patt(const char* str,int index,int top,char* pat,int len);
int main(void) {
    char *str = "()[][]([][((([][])))])";
    char *pat=(char*)malloc(sizeof(char));
    printf("\nÀ¨ºÅÆ¥ÅäÊÇ·ñºÏ·¨ %s \n",patt(str,0,0,pat,(int)strlen(str))?"true":"false");
    return 0;
}
bool patt(const char* str,int index,int top,char* pat,int len){
    if(index == len){
        return 0 == top;
    }
    printf("%c", str[index]);
    if(str[index] == '(' || str[index] == '[') {
        pat[top++] = str[index];
        return patt(str,++index,top,pat,len);
    } else if(str[index] == ')'){
        if (pat[--top] == '(') {
            return patt(str, ++index, top, pat, len);
        }
    } else if(str[index] == ']'){
        if (pat[--top] == '[') {
            return patt(str, ++index, top, pat, len);
        }
    }else{
        return patt(str,++index,top,pat,len);
    }
    return false;
}