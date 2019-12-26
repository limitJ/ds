#include <stdio.h>
#define len(arr) ((int)(sizeof(arr)/sizeof(arr[0])))
int main(int argc, char *argv[])
{
    int arr[] = {1,5,3,8,4,2,9,7};
    for (int i = 0; i < len(arr); ++i) {
        int max = arr[i];
        int index = i;
        for (int j = i+1; j < len(arr); ++j) {
            if(max<arr[j]){
                max = arr[j];
                index = j;
            }
        }
        arr[i] = arr[i]+arr[index]-(arr[index]=arr[i]);
    }
    for (int i = 0; i < len(arr); ++i) {
        printf("%d ", arr[i]);
    }
    return 0;
}
