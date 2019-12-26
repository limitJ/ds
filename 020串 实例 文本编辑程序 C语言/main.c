/*�� ʵ�� �ı��༭
 *QQ: 582521582
 *QQȺ:322085520
 *���л���: gcc
 * */
#include <stdio.h>
#include <string.h>
#include "heapstring.h"
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 32 // �ļ��������
#define LINE_LEN 64 // ÿ���ַ������ֵ+1
#define NAME_LEN 128 // �ļ�����󳤶�(�����̷���·��)+1
#define len(arr) sizeof(arr)/sizeof(arr[0])
void showmenus(void);
void open(void);
void show(void);
void insertline(void);
void save(void);
void deleteline(void);
void modifyline(void);
void search(void);
void replaceline(void);

// ȫ�ֱ���
hstring* T[MAX_LEN];
char lines[LINE_LEN];
char filename[NAME_LEN]="";
FILE *fp = NULL;
int linesCount=0; // �ı�����
int main(void)
{
    int option = -1;
    showmenus();
    while (option!=9) {
        puts("continue choose option!\n");
        scanf("%d", &option); // NOLINT(cert-err34-c)
        switch (option) {
            case 1:open();break;
            case 2:show();break;
            case 3:insertline();break;
            case 4:deleteline();break;
            case 5:modifyline();break;
            case 6:search();break;
            case 7:replaceline();break;
            case 8:save();break;
            default:break;
        }
    }
    puts("exit program!");
    return 0;
}

void replaceline() {// �滻�ַ���
    int i,k;
    int count = 0;
    printf("please input replace pattern str!\n");
    fflush(stdin);
    scanf("%s",lines);
    hstring* s = newhstring(lines);
    fflush(stdin);
    printf("replace str!");
    scanf("%s",lines);
    fflush(stdin);
    hstring* t = newhstring(lines);
    fflush(stdin);
    for(i=0;i<linesCount;i++) // ���в��ҡ��滻
    {
        k=0; // ��ÿ�е�1���ַ������
        while(k!=-1)
        {
            k=indexof(T[i],s,k); // �ɱ��еĵ�k���ַ���ʼ����
            if(k!=-1) // �ҵ�
            {
                count++;
                fflush(stdin);
                printf("the lines of number is: %d\n",i);
                delete(T[i], k, s->len);
                insert(T[i], k, t);
                k += getLength(t);
            }
        }
    }
    if (count == 0) {
        printf("Don't replace!\n");
    }else{
        printf("replace %d\n",count);
    }
}

void search(void) {
    int i,k;
    bool flag = true;// flagΪ�������ұ�־
    char next;
    hstring* s;
    printf("please input pattern str! ");
    scanf("%s",lines);
    s = newhstring(lines);
    fflush(stdin);
    int count = 0;
    for(i=0;i<linesCount&&flag;i++) // ���в���
    {
        k=0; // ÿ�е�0���ַ������
        while(k!=-1)
        {
            k=indexof(T[i],s,k); // �ɱ��еĵ�k���ַ���ʼ����
            if(k!=-1) // �ҵ�
            {
                printf("the lines of number is %d: \n",i);
                print(T[i]);
                ++count;
                printf("is find next pattern str? please input y/n?\n ");
                fflush(stdin);
                next = (char) getchar();
                if(next!='Y'&&next!='y') // �жϲ���
                {
                    flag = false;
                    break;
                }else{
                    k++;
                }
            }
        }
    }
    if(count == 0){
        printf("Don't find!\n");
    }else{
        printf("find %d\n",count);
    }
}

void modifyline(void) {
    int ofline = 0;
    printf("please input modify lines number\n");
    scanf("%d",&ofline); // NOLINT(cert-err34-c)
    if(ofline>=0&&ofline<linesCount) // �кźϷ�
    {
        printf("input new lines words\n");
        fflush(stdin);
        fgets(lines,LINE_LEN,stdin);
        clearhstring(T[ofline]);
        T[ofline] = NULL;
        T[ofline] = newhstring(lines);
        fflush(stdin);
    }
    else
        printf("�кų�����Χ\n");
}

void deleteline(void) {
    int start,end;
    printf("delete from the number of start line to the number of end line!,please input start and end!\n");
    scanf("%d%d",&start,&end); // NOLINT(cert-err34-c)
    if(end<=linesCount&&start>=0){
        int len = end - start;
        for(int i=start;i<linesCount-len;i++)
        {
            clearhstring(T[i]);
            T[i] = NULL;
            T[i] = newhstring(T[i+len]->ch);
        }
        for (int i = linesCount-len; i>linesCount ; i--) {
            clearhstring(T[i]);
            T[i] = NULL;
        }
        linesCount-=len;
    }else{
        printf("�г�����Χ\n");
    }
}

void save(void) {
    puts(filename);
    if ((fp=fopen(filename,"w"))==NULL) {
        puts("filed!");
        exit(-1);
    }else{
        for(int i=0;i<linesCount;i++)
        { // ���ν�ÿ�д����ļ�
            fputs(T[i]->ch, fp);
            clearhstring(T[i]);
        }
    }
    fclose(fp);
    puts("save sceuss!!\n");
}

void insertline(void) {
    int i,oflines,insertLineCount;
    printf("insert info  \n");
    scanf("%d%d",&oflines,&insertLineCount); // NOLINT(cert-err34-c)
    if(linesCount+insertLineCount>MAX_LEN)
    {
        printf("������̫��\n");
        return;
    }
    if(linesCount>oflines&&oflines>=0)
    {
        for(i=linesCount-1;i>=oflines;i--) {
            T[i + insertLineCount] = newhstring(T[i]->ch);
            clearhstring(T[i]);
        }//Ϊ�������ƶ�λ��
        linesCount+=insertLineCount;
        printf("please input insert info:\n");
        fflush(stdin);
        for(i=oflines;i<oflines+insertLineCount;i++)
        {
            fgets(lines,LINE_LEN,stdin);
            T[i] = newhstring(lines);
        }
        show();
    }else {
        printf("�г�����Χ\n");
    }

}

void show(void){
    puts("file infomation!\n");
    for (int i = 0; i < linesCount; ++i) {
        printf("%d: ", i);
        print(T[i]);
    }
    printf("\n");
}
void open(void) {
    puts("please input file name and the length of filename do not over 127 \n ");
    gets(lines);
    strcpy(filename, lines);
    if ((fp = fopen(filename, "r"))==NULL) {
        puts("��ȡ�ļ�ʧ��\n");
    }else{
        while (fgets(lines, LINE_LEN, fp)!=NULL && lines[0]!='\n') // ���ļ�����1���ַ��ɹ�
        {
            if (linesCount >= MAX_LEN) {
                printf("�ļ�̫��\n");
                return;
            }
            //fputs(lines, stdout);
            T[linesCount] = newhstring(lines);
            linesCount++;
        }
        puts("open file sucess!\n\n");
    }
    fclose(fp); // �ر��ļ�
}
void showmenus(void){
    char* menus[9] = {
            "1.open file\n","2.show file\n","3.insert line\n",
            "4.delete line\n","5.modify file\n","6.search string\n",
            "7.replace string\n","8.save to driver\n","9.quit\n",
    };
    for (int j = 0; j < len(menus); ++j) {
        printf("%s", menus[j]);
    }
}