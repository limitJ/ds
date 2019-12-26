//
// Created by zhubin on 2019/1/24.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H

#include "list.h"
typedef List Stack;
bool push(Stack* stack, const void* data);
bool pop(Stack* stack,void** data);
void* peek(Stack *stack);
#endif //STACK_STACK_H
