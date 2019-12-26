//
// Created by QQ 582521582 on 2019/2/21.
//

#ifndef ARRAY_ARRAY_H
#define ARRAY_ARRAY_H

#include <stdbool.h>
#include <stdarg.h>// 标准头文件，提供宏va_start，va_arg和va_end，
#define MAX_ARRAY_DIM 8
typedef struct Array
{
    int *data; // 数组元素基址，由InitArray分配
    int dim; // 数组维数
    int *bounds; // 数组维界基址，由InitArray分配
    int *constants; // 数组映象函数常量基址，由InitArray分配
}array;
bool InitArray(array* arr,int dim,...);
bool value(int* element,array* arr,...);
bool assign(array* arr,int element,...);
int locate(array* arr, va_list ap);
void destroy(array* arr);
#endif //ARRAY_ARRAY_H
