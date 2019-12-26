#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Array.h"
/*
    by zhubin
    C标准:C99
    编译器版本: gcc (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
    IDE: CodeBlocks 17.01
    QQ: 582521582
    Q群:322085520
    字符编码: UTF-8
    平台: Windows 10 1809 专业版 64位
*/
//typedef struct
//{
//    int *array;
//    int size;
//}Array;
Array array_create(int init_size); //创建一个可变长数组
void array_free(Array* a);         //将空间释放
int array_size(Array* a);          //可使用空间大小
int* array_at(Array* a,int index); //获取可变长数组某个单元
void array_inflate(Array* a,int more_size);//增加数组的大小

int main()
{
    int i = 0;
    int temp_size = 0;
    printf("输入你要创建数组的大小：");
    scanf("%d",&temp_size);
    Array a = array_create(temp_size);
    //printf("%d\n",array_size(&a));
    //*array_at(&a,0) = 10;
    //printf("%d\n",*array_at(&a,0));
    int cnt = 0;
    int number = 0;
    printf("开始为你所创建大小为 %d 的数组元素赋值,\n如果超出大小 将自动扩增数组的空间，扩增单位为20个元素的大小不足20 就按20算，并且都赋初值0\n\n按 -1 退出输入\n\n",temp_size);
    while(1)
    {
        printf("为第 [%d] 个元素赋值：",cnt);
        scanf("%d",&number);
        if(number == -1)
        {
            break;
        }
        *array_at(&a,cnt++) = number;
        //scanf("%d",array_at(&a,cnt++));
    }
    printf("你所使用的数组空间大小为%d ：\n",array_size(&a));
    for(i = 0;i<a.size;i++)
    {
        printf("%d ",*array_at(&a,i));
    }
    printf("\n");
    // array_free(&a);
    system("pause");
    return 0;
}
Array array_create(int init_size)
{
    int i = 0;
    Array a;
    a.size = init_size;
    a.array = (int*)malloc(sizeof(int)*init_size);
    for(i = 0;i<a.size;i++)
    {
        a.array[i] = 0;
    }
    return a;
}

void array_free(Array* a)
{
    free(a->array);
    a->array = NULL;
    a->size = 0;

}

int array_size(Array* a)
{
    return a->size;
}

int* array_at(Array* a,int index)
{
    if(index>=a->size)
    {
       // array_inflate(a,index - a->size+1);
       array_inflate(a,(index/BLOCK_SIZE+1)*BLOCK_SIZE - a->size);
    }
    return &(a->array[index]);
}
void array_inflate(Array* a,int more_size)
{
    int* p = (int*)malloc(sizeof(int)*(a->size + more_size));
    int i = 0;
    for( i = 0;i<a->size;i++)
    {
        p[i] = a->array[i];
    }
    for(i = a->size;i<a->size+more_size;i++)
    {
        p[i] = 0;
    }
    free(a->array);
    a->array = p;
    a->size += more_size;
}
