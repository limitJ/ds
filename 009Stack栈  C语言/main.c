/* QQ: 582521582
 * QQ群: 322085520
 * 栈 Stack LIFO先进后出
 * */
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#define len(arr) sizeof(arr)/sizeof(arr[0])
int main() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    list_init(stack, &destroy);
    int QQ[] = {
            5,8,2,5,2,1,5,8,2
    };
    printf("push: ");
    for (int i = 0; i < len(QQ); ++i) {
        push(stack, &QQ[i]);
        printf("%d ", *(int *) peek(stack));//进栈 栈顶元素
    }
    printf("\npop:  ");
    for (int i = 0; i < len(QQ); ++i) {
        printf("%d ", *(int *) peek(stack));//进栈 栈顶元素
        pop(stack, peek(stack));
    }
    return 0;
}