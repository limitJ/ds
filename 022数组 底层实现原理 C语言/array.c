//
// ���ݽṹ ����ĵײ�ʵ�� ����˳���ʾ
// Created by QQ 582521582 on 2019/2/21.
// QQȺ: 322085520
//
#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "readability-misleading-indentation"
#pragma ide diagnostic ignored "cert-msc32-c"
bool InitArray(array* arr,int dim,...){//dim����ܳ���MAX_ARRAY_DIM Ҳ����8
 // ��ά��dim�͸�ά���ȺϷ���������Ӧ������arr��������OK
    int elements=1; // elements������Ԫ����������ֵΪ1(�۳���)
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
            return false; // ��math.h�ж���Ϊ4
        }
        elements*=arr->bounds[i]; //������Ԫ�صĸ���!
    }
    va_end(ap);
    arr->data=(int *)malloc(elements*sizeof(int));//����Ԫ�ط���ռ�
    if (arr->data == NULL) {
        exit(-1);
    }
    arr->constants=(int *)malloc(dim*sizeof(int));
    if (arr->constants == NULL) {
        exit(-1);
    }
    arr->constants[dim-1]=1; //8,2,1 ���ά�ȱ߽� ��Ҫ�����������3,4,2��arr->data�е�λ��
    //Ϊʲô���һ����ָ��Ϊ1 ��Ϊ�����㷨 ֱ����i,j,k����k*1 k����λ�� j*2 ˵����С����ά����2
    for (int i = dim - 2; i >= 0; --i) {
        arr->constants[i]=arr->bounds[i+1]*arr->constants[i+1];
    }
    return true;
}
#pragma clang diagnostic pop

void destroy(array* arr){ // ��������arr
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
    puts("���ٳɹ�");
}

int locate(array* arr, va_list ap){ // value()��assign()���ô˺���
 // ��apָʾ�ĸ��±�ֵ�Ϸ����������Ԫ����A�е���Ե�ַloc
    int bounds = 0;
    int loc = 0;
    for(int i=0;i<arr->dim;i++){
        bounds = va_arg(ap,int);//������ά�� Ҳ���Ǵ�������ĸ����±�
        if (bounds < 0 || bounds >= arr->bounds[i]){
            return -1;
        }
        loc+=arr->constants[i]*bounds;
    }
    return loc;
}

bool value(int* element,array* arr,...){ // ��VC++�У�...֮ǰ���ββ�������������
 // ...����Ϊ��ά���±�ֵ�������±�Ϸ�����element����ֵΪA����Ӧ��Ԫ��ֵ
    va_list ap;
    int loc;
    *element = 0;
    va_start(ap,arr);
    if((loc = locate(arr,ap))==-1) { // ����Locate()
        return -1;
    }
    *element = arr->data[loc];
    return true;
}

bool assign(array* arr,int element,...){ // ...����Ϊ��ά���±�ֵ�������±�Ϸ�����element��ֵ����arr��ָ����Ԫ��
    va_list ap;
    int loc;
    va_start(ap,element);
    if((loc = locate(arr,ap))==-1) { // ����locate()
        return -1;
    }
    arr->data[loc] = element;
    return true;
}