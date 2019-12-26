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
#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED
const int BLOCK_SIZE = 20; //每次增长20个元素大小

typedef struct
{
    int *array;
    int size;
}Array;
Array array_create(int init_size); //创建一个可变长数组
void array_free(Array* a);         //将空间释放
int array_size(Array* a);          //可使用空间大小
int* array_at(Array* a,int index); //获取可变长数组某个单元
void array_inflate(Array* a,int more_size);//增加数组的大小


#endif // ARRAY_H_INCLUDED
