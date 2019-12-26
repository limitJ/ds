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
#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED
const int BLOCK_SIZE = 20; //ÿ������20��Ԫ�ش�С

typedef struct
{
    int *array;
    int size;
}Array;
Array array_create(int init_size); //����һ���ɱ䳤����
void array_free(Array* a);         //���ռ��ͷ�
int array_size(Array* a);          //��ʹ�ÿռ��С
int* array_at(Array* a,int index); //��ȡ�ɱ䳤����ĳ����Ԫ
void array_inflate(Array* a,int more_size);//��������Ĵ�С


#endif // ARRAY_H_INCLUDED
