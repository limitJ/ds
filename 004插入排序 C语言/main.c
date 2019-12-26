/*
 * 插入排序
 * */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#define len(arr) sizeof(arr)/sizeof(arr[0])
int compare(const void *, const void *);
bool insertSort(void *, int, size_t, int(*)(const void *, const void *));
int main(void) {
    int arr[] = {-2,7,3,0,1,8,4,-1,10,9};
    insertSort(arr, len(arr), sizeof(arr[0]), &compare);
    for (int i = 0; i < len(arr); ++i) {
        printf("%d ", arr[i]);
    }
    return 0;
}
bool insertSort(void *data, int len, size_t size, int(*compare)(const void *, const void *)) {
    char *a = data;
    void *key = NULL;
    int k = 0;
    if ((key = (char *) malloc(size)) == NULL) {
        return false;
    }
    for (int i = 1; i < len; i++) {
        memcpy(key, &a[i * size], size);
        k = i - 1;
        while (k >= 0 && compare(&a[k * size], key) > 0) {
            memcpy(&a[(k + 1) * size], &a[k * size], size);
            k--;
        }
        memcpy(&a[(k + 1) * size], key, size);
    }
    free(key);
    return true;
}
int compare(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}
