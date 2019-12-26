/*
 * 基数排序
 * */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define len(arr) ((int)(sizeof(arr)/sizeof(arr[0])))
/*
 * p指位数
 * k指进制
 * */
int radixsort(int* data,int size,int p,int k);
int powint(int k,int n);
int main(int argc, char *argv[])
{
    int arr[] = {302,253,611,901,529,102};
    radixsort(arr, len(arr), 3, 10);
    for (int i = 0; i < len(arr); i++) {
        printf("%d ",arr[i]);
    }
    return 0;
}

int radixsort(int* data,int size,int p,int k){
    int* counts = (int*)malloc(k*sizeof(int));
    int* temp = (int*)malloc(size*sizeof(int));
    int index = 0,pval = 0,i = 0,j = 0;
    if (counts == NULL || temp == NULL) {
        return -1;
    }
    for (int n = 0; n < p; ++n) {
        for (int i = 0; i < k; ++i) {
            counts[i] = 0;
        }
        pval = powint(k,n);
        for (int i = 0; i < size; ++i) {
            index = (int)(data[i] / pval) % k;
            counts[index]++;
        }
        for (int i = 1; i < k; ++i) {
            counts[i]+=counts[i - 1];
        }
        for (int i = size-1; i >= 0; --i) {
            index = (int)(data[i]/pval)%k;
            temp[counts[index]-1] = data[i];
            counts[index]--;
        }
        memcpy(data, temp, size*sizeof(int));
    }
    free(counts);
    free(temp);
    return 0;
}

int powint(int k,int n){
    int sum = 1;
    while(n--){
        sum*=k;
    }
    return sum;
}
