/*
 * ��������
 *  ������ �� ջ
 * QQ 582521582
 * QQȺ 322085520
 * Created by zhubin on 2019/3/13
 * �������л���
 * OS windows 10 1809
 * �������汾 MinGW-8.1.0 gcc
 * c��׼ c11
 * cmake�汾 3.13.1
 * IDE CLion 2018.3.5
 * ������
 *  ������ʵ�ּ�ǿ�ĵ����� ����ͷ�巨�ķ�ʽ�������ݴ洢
 * ����ͷ�巨�����ݽṹ ջ�Ĵ洢˳��һ�� ���������һ��
 * ����ͬʱʵ��ջ�����ݽṹ��pop push peek����
 * ͬʱ������ʹ�õݹ� Ҳ����ģ��ʵ�ֶ��еĴ�ӡ����printQueue
 * ��Ϊ�ǵ������ջ�����ݽṹ ����ת���ջ ���Ե��ɶ���ʹ�ã�
 * ת��ķ�ʽ�ܼ� ����mallocһ��list �ظ����һ�����ݾͿ���
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
    };//׼����������
    printf("�����Ƿ�Ϊ�� %s\n",boolean(isEmpty(list)));
    for (int i = 0; i < len(data); i++){
        ins(list, i + 1, data[i]);
    }
    printf("��ջ��ӡ: ");
    print(list);//��ӡ���� ������β�巨 ���Դ�ӡ˳���� ��ջ����˳��
    printf("�����Ƿ�Ϊ�� %s\n",boolean(isEmpty(list)));
    printf("���д�ӡ: ");
    printQueue(list->head);//�õݹ�ķ�ʽ��ӡ���� ��ӡ��˳���� ����
    printf("\n");//����
    printf("����ĳ��� %d\n", getLength(list));
    int elem = 0;
    bool f1 = getElement(list,3,&elem);
    printf("%s ��3��Ԫ���� %d\n", boolean(f1) ,elem);//ע���ǳ�ջ��˳�� ���Է����ǵ�����3��
    int f2 = getNext(list,4,&elem);
    printf("%s ��4��Ԫ�ص���һ��Ԫ����%d\n", boolean(f2), elem);
    printf("ջ��Ԫ���� %d\n", peek(list));
    printf("ջβ��Ԫ���� %d\n", poll(list));
    bool f3 = del(list,2,&elem);
    printf("%s ɾ����2��Ԫ�� %d\n", boolean(f3), elem);
    print(list);
    printf("����ĳ��� %d\n", getLength(list));
    bool f4 = ins(list, 2, elem);
    getElement(list,2,&elem);
    printf("%s ��ӵ�2��Ԫ�� %d\n", boolean(f4),elem);
    print(list);
    printf("����ĳ��� %d\n", getLength(list));
    ListElement* element = getLocElement(list->head,5);
    if (element == NULL) {
        printf("û���ҵ���ͬԪ��!\n");
    }else{
        printf("����Ԫ��5������ڵ�Ԫ���� %d\n",element->data);
    }
    int index = getLength(list);
    printf("�����Ƴ�ջ��Ԫ��: ");
    for (int i = 0; i < index; ++i) {
        printf("%d ", peek(list));
        pop(list, &elem);
    }
    printf("����ĳ��� %d\n", getLength(list));
    printf("������ջ: ");
    for (int i = 0; i < len(data); ++i) {
        push(list, data[i]);
        printf("%d ", peek(list));
    }
    printf("����ĳ��� %d\n", getLength(list));
    bool f5 = clearList(list);
    printf("�������Ԫ������ջ�Ƿ�ɹ� %s\n", boolean(f5));
    printf("����ĳ��� %d\n", getLength(list));
    bool f6 = destroy(list);
    printf("��������ջ�Ƿ�ɹ� %s\n", boolean(f6));
    printf("�������!\n");
    system("pause");
    return 0;
}