/*
 *
 * �� n(n>=0)���ڵ�����޼�
 * һ�ŷǿ�����
 * ����һ�����ڵ�root
 * ����˳��洢�ṹ insertChild delete��д�� ����
 * �����鷳 Ҳ��д��
 *
 * */
#include "sqbinarytree.h"
int main(void)
{
    int sqbt[MAX_TREE_SIZE] = {
            1,2,3,4,5,6,0,7,8,9,0,10,0,0,0,0
    };
    //��������Ӧ�洢��ʽ����
    /*0����ռ� ��ʽ(i+1)/2 - 1���ڸýڵ�ĸ��ڵ���� iΪ��ǰλ�ýڵ� �սڵ���ǲ����к��ӽڵ��
     * ͬ���� ���ӽڵ�ĸ��׽ڵ��ǲ�����Ϊ0�սڵ�� ������create���жϱ��������6�ĳ�0 �ͻᱨ��
     *            1
     *      2           3
     *   4     5     6     0
     *  7 8   9 0  10 0   0 0
     *
     * */
    InitBiTree(sqbt);
    CreateBiTree(sqbt);
    printf("�ǹ�Ϊ�գ�%d\n", isEmpty(sqbt));
    printf("��� %d\n", Depth(sqbt));
    printf("����: %d\n", Root(sqbt));
}