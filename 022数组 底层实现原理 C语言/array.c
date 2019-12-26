//
// 数据结构 数组的底层实现 数组顺序表示
// Created by QQ 582521582 on 2019/2/21.
// QQ群: 322085520
//
#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "readability-misleading-indentation"
#pragma ide diagnostic ignored "cert-msc32-c"
bool InitArray(array* arr,int dim,...){//dim最大不能超过MAX_ARRAY_DIM 也就是8
 // 若维数dim和各维长度合法，则构造相应的数组arr，并返回OK
    int elements=1; // elements是数组元素总数，初值为1(累乘器)
    va_list ap;
    if(dim<1||dim>MAX_ARRAY_DIM)
    return false;
    arr->dim=dim;
    arr->bounds=(int *)malloc(dim*sizeof(int));
    if(arr->bounds == NULL){
        exit(-1);
    }
    va_start(ap,dim);
    for(int i=0;i<dim;++i)
    {
        arr->bounds[i]=va_arg(ap,int);
        if(arr->bounds[i]<0){
            return false; // 在math.h中定义为4
        }
        elements*=arr->bounds[i]; //计算总元素的个数!
    }
    va_end(ap);
    arr->data=(int *)malloc(elements*sizeof(int));//给总元素分配空间
    if (arr->data == NULL) {
        exit(-1);
    }
    arr->constants=(int *)malloc(dim*sizeof(int));
    if (arr->constants == NULL) {
        exit(-1);
    }
    arr->constants[dim-1]=1; //8,2,1 这个维度边界 主要用于求出数组3,4,2在arr->data中的位置
    //为什么最后一个数指定为1 因为后续算法 直接是i,j,k中用k*1 k就是位置 j*2 说明最小数组维度是2
    for (int i = dim - 2; i >= 0; --i) {
        arr->constants[i]=arr->bounds[i+1]*arr->constants[i+1];
    }
    return true;
}
#pragma clang diagnostic pop

void destroy(array* arr){ // 销毁数组arr
    if (arr->data) {
        free(arr->data);
    }
    if (arr->bounds) {
        free(arr->bounds);
    }
    if (arr->constants) {

        free(arr->constants);
    }
    arr->data=arr->bounds=arr->constants=NULL;
    arr->dim=0;
    free(arr);
    puts("销毁成功");
}

int locate(array* arr, va_list ap){ // value()、assign()调用此函数
 // 若ap指示的各下标值合法，则求出该元素在A中的相对地址loc
    int bounds = 0;
    int loc = 0;
    for(int i=0;i<arr->dim;i++){
        bounds = va_arg(ap,int);//传的是维度 也就是传入数组的各个下标
        if (bounds < 0 || bounds >= arr->bounds[i]){
            return -1;
        }
        loc+=arr->constants[i]*bounds;
    }
    return loc;
}

bool value(int* element,array* arr,...){ // 在VC++中，...之前的形参不能是引用类型
 // ...依次为各维的下标值，若各下标合法，则element被赋值为A的相应的元素值
    va_list ap;
    int loc;
    *element = 0;
    va_start(ap,arr);
    if((loc = locate(arr,ap))==-1) { // 调用Locate()
        return -1;
    }
    *element = arr->data[loc];
    return true;
}

bool assign(array* arr,int element,...){ // ...依次为各维的下标值，若各下标合法，则将element的值赋给arr的指定的元素
    va_list ap;
    int loc;
    va_start(ap,element);
    if((loc = locate(arr,ap))==-1) { // 调用locate()
        return -1;
    }
    arr->data[loc] = element;
    return true;
}