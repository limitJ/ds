#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heapstring.h"
#define boolean(flag) flag?"true":"false"
int main(void) {
    hstring* hstr1 = newhstring("123456");
    print(hstr1);
    printf("字符串是否为空: %s\n",boolean(isEmpty(hstr1)));

    int com = compare(newhstring("abcd"), newhstring("abcd")); //1代表大于 0等于 -1小于
    printf("字符串比较结果: %d\n", com);

    printf("字符串长度: %d\n",getLength(newhstring("asaas")));//获取长度

    clearhstring(hstr1);
    printf("清空字符串后的长度:%d\n",getLength(hstr1));//获取长度

    hstring *hstr2 = newhstring("abcde");
    append(hstr2, newhstring("aaa"));//字符串拼接
    printf("拼接后的字符串: ");
    print(hstr2); //拼接后的字符串
    printf("字符串长度: %d\n",getLength(hstr2));//获取拼接后字符串的长度

    hstring *subs = substring(newhstring("abcdefg"), 0, 7);
    printf("截取后的字符串: ");
    print(subs);

    int index = indexof(newhstring("abcdeeabsa"), newhstring("eea"), 0);
    printf("索引位置: %d\n", index);

    hstring *hstr3 = newhstring("abcd");
    insert(hstr3, 1, newhstring("eea"));
    printf("插入后的字符串: ");
    print(hstr3);

    hstring *hstr4 = newhstring("abcadc");
    delete(hstr4, 0, 2);
    printf("删除后的字符串: ");
    print(hstr4);

    hstring *hstr5 = newhstring("I Love Java And Java");
    replace(hstr5, newhstring("Java"), newhstring("Python"));
    printf("替换后的字符串: ");
    print(hstr5);
    return 0;
}