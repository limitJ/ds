#include "stack.h"
/*
 *  数据结构 二叉树树的循环遍历 栈 (为二叉树遍历写了一个栈 书上都是伪代码 哭唧唧)
 *  运行环境 Arch Linux (Manjaro Linux 18.04)KDE
 *  编译器 LLVM Clang 8.0
 *  请不要尝试在其他编译器中运行
 *  qq 582521582
 *  QQ群 322085520
 * */
void initStack(Stack* stack){
	stack->head = NULL;
	stack->size = 0;
}
bool isEmpty(Stack* stack){
	return 0 == stack->size;
}
bool push(Stack* stack, Node* element){
    StackElement* new_element = (StackElement*)malloc(sizeof(StackElement));
    assert(new_element != NULL);
    assert(element!=NULL);
    new_element->element = element;
    new_element->next = stack->head;
    stack->head = new_element;
	stack->size++;
	return true;
}
bool pop(Stack* stack){
	if (stack->size == 0){
		return false;
	}
	StackElement* old_element = stack->head;
    if (stack->head->next == NULL) {
        stack->head = NULL;
    }else{
        stack->head = stack->head->next;
    }
	free(old_element);
	stack->size--;
	return true;
}
Node* peek(Stack* stack){
	return stack->head->element;
}
void clearStack(Stack* stack){
    while (!isEmpty(stack)) {
        pop(stack);
    }
}