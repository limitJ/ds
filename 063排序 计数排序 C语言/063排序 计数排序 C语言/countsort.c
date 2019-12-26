/*
 *
 * 计数排序
 * 计数排序只适用于整数的排序 局限性比较大
 * 优点是效率高 而且是非比较类型的排序
 * 时间复杂度是O(n+k) k指数组中的max值
 * */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define len(arr) ((int)(sizeof(arr)/sizeof(arr[0])))
int getMax(int* arr,int len);
int countsort(int* data,int size,int max);
int main(int argc, char *argv[])
{
    int arr[] = {0,4,1,3,1,2,4,1};
    countsort(arr, len(arr), getMax(arr,len(arr))+1);
    for (int i = 0; i < len(arr); ++i) {
        printf("%d ",arr[i]);
    }
    return 0;
}
int countsort(int* data,int size,int max){
    int * counts = (int*)malloc(sizeof(int)*max);
    int * temp = (int*)malloc(sizeof(int)*size);
    if (counts == ((void*)0) || temp == (void*)0) {
        return -1;
    }
    for (int i = 0; i < max; i++) {
        counts[i] = 0;
    }
    for (int i = 0; i < size; ++i) {
        counts[data[i]]+=1;
    }
    for (int i = 1; i < max; ++i) {
        counts[i]+=counts[i-1];
    }
    for (int i = size-1; i >= 0; --i) {
        temp[counts[data[i]] - 1] = data[i];
        counts[data[i]] = counts[data[i]] - 1;
    }
    memcpy(data, temp, size*sizeof(int));
    free(counts);
    free(temp);
    return 0;
}

int getMax(int* arr,int len){
    int max = arr[0];
    for (int i = 0; i < len; ++i) {
        if(max<arr[i]){
            max = arr[i];
        }
    }
    return max;

}
