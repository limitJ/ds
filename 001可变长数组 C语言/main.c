#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Array.h"
/*
    by zhubin
    C��׼:C99
    �������汾: gcc (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
    IDE: CodeBlocks 17.01
    QQ: 582521582
    QȺ:322085520
    �ַ�����: UTF-8
    ƽ̨: Windows 10 1809 רҵ�� 64λ
*/
//typedef struct
//{
//    int *array;
//    int size;
//}Array;
Array array_create(int init_size); //����һ���ɱ䳤����
void array_free(Array* a);         //���ռ��ͷ�
int array_size(Array* a);          //��ʹ�ÿռ��С
int* array_at(Array* a,int index); //��ȡ�ɱ䳤����ĳ����Ԫ
void array_inflate(Array* a,int more_size);//��������Ĵ�С

int main()
{
    int i = 0;
    int temp_size = 0;
    printf("������Ҫ��������Ĵ�С��");
    scanf("%d",&temp_size);
    Array a = array_create(temp_size);
    //printf("%d\n",array_size(&a));
    //*array_at(&a,0) = 10;
    //printf("%d\n",*array_at(&a,0));
    int cnt = 0;
    int number = 0;
    printf("��ʼΪ����������СΪ %d ������Ԫ�ظ�ֵ,\n���������С ���Զ���������Ŀռ䣬������λΪ20��Ԫ�صĴ�С����20 �Ͱ�20�㣬���Ҷ�����ֵ0\n\n�� -1 �˳�����\n\n",temp_size);
    while(1)
    {
        printf("Ϊ�� [%d] ��Ԫ�ظ�ֵ��",cnt);
        scanf("%d",&number);
        if(number == -1)
        {
            break;
        }
        *array_at(&a,cnt++) = number;
        //scanf("%d",array_at(&a,cnt++));
    }
    printf("����ʹ�õ�����ռ��СΪ%d ��\n",array_size(&a));
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
