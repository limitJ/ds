/*串 实例 文本编辑
 *QQ: 582521582
 *QQ群:322085520
 *运行环境: gcc
 * */
#include <stdio.h>
#include <string.h>
#include "heapstring.h"
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 32 // 文件最大行数
#define LINE_LEN 64 // 每行字符数最大值+1
#define NAME_LEN 128 // 文件名最大长度(包括盘符、路径)+1
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

// 全局变量
hstring* T[MAX_LEN];
char lines[LINE_LEN];
char filename[NAME_LEN]="";
FILE *fp = NULL;
int linesCount=0; // 文本行数
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

void replaceline() {// 替换字符串
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
    for(i=0;i<linesCount;i++) // 逐行查找、替换
    {
        k=0; // 由每行第1个字符起查找
        while(k!=-1)
        {
            k=indexof(T[i],s,k); // 由本行的第k个字符开始查找
            if(k!=-1) // 找到
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
    bool flag = true;// flag为继续查找标志
    char next;
    hstring* s;
    printf("please input pattern str! ");
    scanf("%s",lines);
    s = newhstring(lines);
    fflush(stdin);
    int count = 0;
    for(i=0;i<linesCount&&flag;i++) // 逐行查找
    {
        k=0; // 每行第0个字符起查找
        while(k!=-1)
        {
            k=indexof(T[i],s,k); // 由本行的第k个字符开始查找
            if(k!=-1) // 找到
            {
                printf("the lines of number is %d: \n",i);
                print(T[i]);
                ++count;
                printf("is find next pattern str? please input y/n?\n ");
                fflush(stdin);
                next = (char) getchar();
                if(next!='Y'&&next!='y') // 中断查找
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
    if(ofline>=0&&ofline<linesCount) // 行号合法
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
        printf("行号超出范围\n");
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
        printf("行超出范围\n");
    }
}

void save(void) {
    puts(filename);
    if ((fp=fopen(filename,"w"))==NULL) {
        puts("filed!");
        exit(-1);
    }else{
        for(int i=0;i<linesCount;i++)
        { // 依次将每行存入文件
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
        printf("插入行太多\n");
        return;
    }
    if(linesCount>oflines&&oflines>=0)
    {
        for(i=linesCount-1;i>=oflines;i--) {
            T[i + insertLineCount] = newhstring(T[i]->ch);
            clearhstring(T[i]);
        }//为插入行移动位置
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
        printf("行超出范围\n");
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
        puts("读取文件失败\n");
    }else{
        while (fgets(lines, LINE_LEN, fp)!=NULL && lines[0]!='\n') // 由文件读入1行字符成功
        {
            if (linesCount >= MAX_LEN) {
                printf("文件太大\n");
                return;
            }
            //fputs(lines, stdout);
            T[linesCount] = newhstring(lines);
            linesCount++;
        }
        puts("open file sucess!\n\n");
    }
    fclose(fp); // 关闭文件
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