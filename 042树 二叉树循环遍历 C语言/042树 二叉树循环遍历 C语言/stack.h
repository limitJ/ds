#ifndef PROJECT1_STACK_H
#define PROJECT1_STACK_H
/*
 *  数据结构 二叉树树的循环遍历 栈 (为二叉树遍历写了一个栈 书上都是伪代码 哭唧唧)
 *  运行环境 Arch Linux (Manjaro Linux 18.04)KDE
 *  编译器 LLVM Clang 8.0
 *  请不要尝试在其他编译器中运行
 *  qq 582521582
 *  QQ群 322085520
 * */
#include "binarytree.h"
typedef struct StackElement{
	Node* element;
	struct StackElement* next;
}StackElement;
typedef struct Stack{
	StackElement* head;
	int size;
}Stack;
void initStack(Stack* stack);
bool isEmpty(Stack* stack);
bool push(Stack* stack, Node* element);
bool pop(Stack* stack);
Node* peek(Stack* stack);
void clearStack(Stack* stack);
#endif
