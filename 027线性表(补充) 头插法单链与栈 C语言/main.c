/*
 * 程序名称
 *  单链表 与 栈
 * QQ 582521582
 * QQ群 322085520
 * Created by zhubin on 2019/3/13
 * 程序运行环境
 * OS windows 10 1809
 * 编译器版本 MinGW-8.1.0 gcc
 * c标准 c11
 * cmake版本 3.13.1
 * IDE CLion 2018.3.5
 * 程序简介
 *  本程序实现加强的单链表 按照头插法的方式进行数据存储
 * 由于头插法和数据结构 栈的存储顺序一致 因此利用这一点
 * 所以同时实现栈的数据结构的pop push peek函数
 * 同时程序多次使用递归 也可以模拟实现队列的打印函数printQueue
 * 因为是单链表的栈的数据结构 所以转序后栈 可以当成队列使用！
 * 转序的方式很简单 重新malloc一个list 重复添加一次数据就可以
 * */
#include <stdio.h>
#include "list.h"
int main(void){
    List* list = newObject(List);
    initList(list);
    int data[9] = {
            [0] = 5, [1] = 8, [2] = 2,
            [3] = 5, [4] = 2, [5] = 1,
            [6] = 5, [7] = 8, [8] = 2,
    };//准备测试数据
    printf("链表是否为空 %s\n",boolean(isEmpty(list)));
    for (int i = 0; i < len(data); i++){
        ins(list, i + 1, data[i]);
    }
    printf("出栈打印: ");
    print(list);//打印链表 由于是尾插法 所以打印顺序是 出栈的书顺序
    printf("链表是否为空 %s\n",boolean(isEmpty(list)));
    printf("队列打印: ");
    printQueue(list->head);//用递归的方式打印链表 打印的顺序是 队列
    printf("\n");//换行
    printf("链表的长度 %d\n", getLength(list));
    int elem = 0;
    bool f1 = getElement(list,3,&elem);
    printf("%s 第3个元素是 %d\n", boolean(f1) ,elem);//注意是出栈的顺序 所以反而是倒数第3个
    int f2 = getNext(list,4,&elem);
    printf("%s 第4个元素的下一个元素是%d\n", boolean(f2), elem);
    printf("栈顶元素是 %d\n", peek(list));
    printf("栈尾的元素是 %d\n", poll(list));
    bool f3 = del(list,2,&elem);
    printf("%s 删除第2个元素 %d\n", boolean(f3), elem);
    print(list);
    printf("链表的长度 %d\n", getLength(list));
    bool f4 = ins(list, 2, elem);
    getElement(list,2,&elem);
    printf("%s 添加第2个元素 %d\n", boolean(f4),elem);
    print(list);
    printf("链表的长度 %d\n", getLength(list));
    ListElement* element = getLocElement(list->head,5);
    if (element == NULL) {
        printf("没有找到相同元素!\n");
    }else{
        printf("包含元素5的链表节点元素是 %d\n",element->data);
    }
    int index = getLength(list);
    printf("依次移除栈顶元素: ");
    for (int i = 0; i < index; ++i) {
        printf("%d ", peek(list));
        pop(list, &elem);
    }
    printf("链表的长度 %d\n", getLength(list));
    printf("依次入栈: ");
    for (int i = 0; i < len(data); ++i) {
        push(list, data[i]);
        printf("%d ", peek(list));
    }
    printf("链表的长度 %d\n", getLength(list));
    bool f5 = clearList(list);
    printf("清空链表元素链表栈是否成功 %s\n", boolean(f5));
    printf("链表的长度 %d\n", getLength(list));
    bool f6 = destroy(list);
    printf("销毁链表栈是否成功 %s\n", boolean(f6));
    printf("程序结束!\n");
    system("pause");
    return 0;
}