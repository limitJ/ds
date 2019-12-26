//
// Created by zhubin on 2019/1/24.
//
#include <stdlib.h>
#include "list.h"
#include "stack.h"
bool push(Stack* stack, const void* data){//压栈
    return list_ins_next(stack,NULL, data);
}
bool pop(Stack* stack,void** data){//出栈
    return list_rem_next(stack, NULL, data);
}
void* peek(Stack *stack){//栈顶元素
    return stack->head ==NULL?NULL:stack->head->data;
}

