#include <stdio.h>
#include <stdlib.h>
#define len(arr) ((int)sizeof(arr)/sizeof(arr[0]))
int compare(const void* key1,const void* key2);
int bisearch(int* arr,int left,int right,int key);
int main(int argc, char *argv[])
{
    int arr[] = {0,1,9,16,23,84,97,123,233};
    int key = 84;
    int find = bisearch(arr, 0, len(arr)-1,key);
    printf("%d\n",find);
    return 0;
}
int compare(const void* key1,const void* key2){
    int cmpval =  *(int*)key1 - *(int*)key2;
    if (cmpval>0) {
        return 1;
    }else if(cmpval < 0){
        return -1;
    }else{
        return 0;
    }
}
int bisearch(int* arr,int left,int right,int key){
    int middle = 0;
    while(left<=right){
        middle = (left+right)/2;
        switch (compare(&arr[middle], &key)) {
            case 1:
                right = middle-1;
                break;
            case -1:
                left = middle+1;
                break;
            case 0:
                return middle;
        }
    }
    return -1;
}
