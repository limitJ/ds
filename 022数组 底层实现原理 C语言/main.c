#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"
#define  random(a,b) rand()%b+a
int main(void){
    srand((unsigned int) time(NULL)); // NOLINT(cert-msc32-c,cert-msc51-cpp)
    array *arr = (array*)malloc(sizeof(array));
    InitArray(arr,3,3,4,2); // 构造3×4×2的3维数组arr
    printf("arr->bounds=");
    for(int i=0;i<arr->dim;i++) { // 顺序输出arr->bounds
        printf("%d ", arr->bounds[i]);
    }
    printf("\narr->constants=");
    for(int i=0;i<arr->dim;i++) { // 顺序输出arr->constants
        printf("%d ", arr->constants[i]);
    }
    printf("\nbounds[%d][%d][%d]=\n",arr->bounds[0],arr->bounds[1],arr->bounds[2]);
    for(int i=0;i<arr->bounds[0];i++){
        for(int j=0;j<arr->bounds[1];j++){
            for(int k=0;k<arr->bounds[2];k++){
                int element = 0;
                assign(arr,random(1,100),i,j,k); // 将1-100之间的随机数赋值给arr[i][j][k] NOLINT(cert-msc30-c,cert-msc50-cpp)
                value(&element, arr, i, j, k); // 将A[i][j][k]的值赋给element 为了输出
                printf("A[%d][%d][%d]=%2d ",i,j,k,element); // 输出A[i][j][k]
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("arr->data=\n");
    for(int i=0;i<arr->bounds[0]*arr->bounds[1]*arr->bounds[2];i++){ // 顺序输出arr->data
        printf("%d ",arr->data[i]);
        if (i % (arr->bounds[1] * arr->bounds[2]) == arr->bounds[1] * arr->bounds[2] - 1) {
            printf("\n");
        }
    }
    printf("arr->dim=%d\n",arr->dim);
    destroy(arr);//销毁数组
    return 0;
}