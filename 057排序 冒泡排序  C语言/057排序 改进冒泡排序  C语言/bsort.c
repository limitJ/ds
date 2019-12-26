#include <stdio.h>
#include <stdbool.h>
#define len(arr) ((int)(sizeof(arr)/sizeof(arr[0])))
int main(int argc, char *argv[])
{
    int arr[] = {5,1,9,7,4,1,2,3,4,90};
    bool change = true;
    for (int i = len(arr)-1; i >=0 && change; --i) {
        change = false;
        for (int j = 0; j < i; ++j) {
            if(arr[j]>arr[j+1]){
                arr[j] = arr[j]+arr[j+1]-(arr[j+1]=arr[j]);
                change = true;
            }
        }
    }
    for (int i = 0; i < len(arr); ++i) {
        printf("%d ", arr[i]);
    }
    return 0;
}
