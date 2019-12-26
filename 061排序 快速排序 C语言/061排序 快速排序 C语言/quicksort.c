/*
 * 快速排序
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <memory.h>
#define randint(a,b) rand()%(b-a+1)+a
#define len(arr) ((int)(sizeof(arr)/sizeof(arr[0])))
int compare(const void* key1,const void* key2);
static int partition(void* arr,int esize,int i,int k,
        int compare(const void* key1,const void* key2));
int quicksort(void* data,int size,int esize,int i,int k,
        int (*compare)(const void* key1,const void* key2));
int main(int argc, char *argv[]){
    int arr[] = {24,52,11,94,28,36,14,80};
    quicksort(arr, 8, 4, 0, 7, &compare);
    for (int i = 0; i < 8; i++) {
        printf("%d ",arr[i]);
    }
    return 0;
}
int quicksort(void* data,int size,int esize,int i,int k,
        int (*compare)(const void* key1,const void* key2)){
    int j = 0;
    while(i<k){
        j = partition(data, esize, i, k, compare);
        if (j<0) {
            return -1;
        }
        //printf("%d %d %d\n",j,i,k);
        if (quicksort(data, size, esize, i, j, compare)<0) {
            return -1;
        }
        i = j+1;
    }
    return 0;
}
static int partition(void* data,int esize,int i,int k,
       int compare(const void* key1,const void* key2)){
    srand((unsigned)time((void*)0));
    char* a = data;
    void* pval = malloc(esize);
    void* temp = malloc(esize);
    if (pval == ((void*)0) || temp == ((void*)0)) {
        free(pval);
        free(temp);
        return -1;
    }
    int randval[3] = {
        [0] = randint(i, k),
        [1] = randint(i, k),
        [2] = randint(i, k),
    };
    qsort(randval, 3, sizeof(int), compare);
    int middle = randval[1];
    memcpy(pval,&a[middle*esize],esize);
    //用随机三个数中取出一个中间值 作为快速排序的枢纽值
    ++k;
    --i;
    while(i<k){
        while(compare(&a[(--k)*esize],pval)>0);//从右边开始找比枢纽值小的数的位置
        while(compare(&a[(++i)*esize],pval)<0);//从左边开始找比枢纽值大的数的位置
        //printf("%d %d %d ------\n",*(int*)pval,k,i);
        if(i>=k){
            break;
        }else{
            //找到了就交换
            memcpy(temp, &a[i*esize], esize);
            memcpy(&a[i*esize], &a[k*esize], esize);
            memcpy(&a[k*esize],temp, esize);
        }
    }
    free(pval);
    free(temp);
    return k;
}
int compare(const void* key1,const void* key2){
    int cmpval = *(int*)key1 - *(int*)key2;
    if(cmpval>0){
        return 1;
    }else if(cmpval<0){
        return -1;
    }else{
        return 0;
    }
}
