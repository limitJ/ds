#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heapstring.h"
#define boolean(flag) flag?"true":"false"
int main(void) {
    hstring* hstr1 = newhstring("123456");
    print(hstr1);
    printf("�ַ����Ƿ�Ϊ��: %s\n",boolean(isEmpty(hstr1)));

    int com = compare(newhstring("abcd"), newhstring("abcd")); //1������� 0���� -1С��
    printf("�ַ����ȽϽ��: %d\n", com);

    printf("�ַ�������: %d\n",getLength(newhstring("asaas")));//��ȡ����

    clearhstring(hstr1);
    printf("����ַ�����ĳ���:%d\n",getLength(hstr1));//��ȡ����

    hstring *hstr2 = newhstring("abcde");
    append(hstr2, newhstring("aaa"));//�ַ���ƴ��
    printf("ƴ�Ӻ���ַ���: ");
    print(hstr2); //ƴ�Ӻ���ַ���
    printf("�ַ�������: %d\n",getLength(hstr2));//��ȡƴ�Ӻ��ַ����ĳ���

    hstring *subs = substring(newhstring("abcdefg"), 0, 7);
    printf("��ȡ����ַ���: ");
    print(subs);

    int index = indexof(newhstring("abcdeeabsa"), newhstring("eea"), 0);
    printf("����λ��: %d\n", index);

    hstring *hstr3 = newhstring("abcd");
    insert(hstr3, 1, newhstring("eea"));
    printf("�������ַ���: ");
    print(hstr3);

    hstring *hstr4 = newhstring("abcadc");
    delete(hstr4, 0, 2);
    printf("ɾ������ַ���: ");
    print(hstr4);

    hstring *hstr5 = newhstring("I Love Java And Java");
    replace(hstr5, newhstring("Java"), newhstring("Python"));
    printf("�滻����ַ���: ");
    print(hstr5);
    return 0;
}