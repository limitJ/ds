#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define NULL ((void*)0)
#define len(arr) ((int)(sizeof(arr)/sizeof(arr[0])))
int compare(const void* key1,const void* key2);
int insertSort(void* arr,int size,int esize,
        int (*compare)(const void* key1,const void* key2));
int main(int argc, char *argv[])
{
    int arr[] = {1,5,3,8,4,2,9,7};
    insertSort(arr, len(arr),sizeof(arr[0]), &compare);
    for (int i = 0; i < len(arr); ++i) {
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}
//插入排序 泛型
int insertSort(void* arr,int size,int esize,
        int(*compare)(const void* key1,const void* key2)){
    void* key = (char*)malloc(esize);
    if (key == NULL) {
        return -1;
    }
    int i = 0;
    for (int j = 1; j < size; ++j) {
        memcpy(key,&arr[j*esize],esize);
        i = j-1;
        while(i>=0 && compare(&arr[i*esize],key)>0){
            memcpy(&arr[(i+1)*esize], &arr[i*esize], esize);
            i--;
        }
        memcpy(&arr[(i+1)*esize],key,esize);
    }
    free(key);
    return 0;
}
//自定义比较器
int compare(const void* key1,const void* key2){
    return *(int*)key1 - *(int*)key2;
}
