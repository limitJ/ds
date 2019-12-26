/*
 * 并归排序
 * */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <memory.h>
#define len(arr) ((int)(sizeof(arr)/sizeof(arr[0])))
int compare(const void* key1,const void* key2);
static int merge(void* data,int esize,int i,int j,int k,
        int compare(const void* key1,const void* key2));
int mergersort(void* data,int size,int esize,int i,int k,
        int (*compare)(const void* key1,const void* key2));
int main(int argc, char *argv[]){
    int arr[] = {24,52,11,94,28,36,14,80};
    mergersort(arr, len(arr), sizeof(arr[0]), 0, len(arr)-1, compare);
    for (int i = 0; i < 8; i++) {
        printf("%d ",arr[i]);
    }
    return 0;
}

int mergersort(void* data,int size,int esize,int i,int k,
        int (*compare)(const void* key1,const void* key2)){
    int j;
    if(i < k){
        j = (int)((i+k-1)/2);
        if (mergersort(data, size, esize, i, j, compare) < 0) {
            return -1;
        }
        if (mergersort(data, size, esize, j+1, k, compare) < 0) {
            return -1;
        }
        if (merge(data, esize, i, j, k, compare) < 0) {
            return -1;
        }
    }
    return 0;
}

static int merge(void* data,int esize,int i,int j,int k,
        int compare(const void* key1,const void* key2)){
    char *arr = data;
    char* m = (char*)malloc(esize*(k-i+1));
    int ipos = i;
    int jpos = j+1;
    int mpos = 0;
    if(m == ((void*)0)){
        return -1;
    }
    while(ipos<=j || jpos<=k){
        if (ipos > j) {
            while(jpos <= k){
                memcpy(&m[mpos*esize], &arr[jpos*esize], esize);
                jpos++;
                mpos++;
            }
            continue;
        }else if(jpos > k){
            while(ipos <= j){
                memcpy(&m[mpos*esize], &arr[ipos*esize], esize);
                ipos++;
                mpos++;
            }
            continue;

        }

        if (compare(&arr[ipos*esize],&arr[jpos*esize]) < 0) {
            memcpy(&m[mpos*esize], &arr[ipos*esize], esize);
            ipos++;
            mpos++;
        }else{
            memcpy(&m[mpos*esize], &arr[jpos*esize], esize);
            jpos++;
            mpos++;

        }
    }
    memcpy(&arr[i*esize], m, esize*(k-i+1));
    free(m);
    return 0;
}

int compare(const void* key1,const void* key2){
    return 1*(*(int*)key1 - *(int*)key2);
}
