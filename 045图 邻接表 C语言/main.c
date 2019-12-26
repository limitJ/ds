/*
 * ͼ �ڽӱ�
 * ��ε���Ĵ�������̫��ɬ�Ѷ��� ���������дͼ�Ĵ���ʵ��
 * Ϊ�˾�������� �����ظ����� ����ֻʵ�� ������
 * ����������ͼ ����ͼ ������������ͬС�� �ı�ĵط����� ������ﲻȥʵ������3��
 * QQ 582521582
 * QQȺ 322085520
 * ��������ȫ����ʵ�� ������ˮƽ���� ������������ ��ӭ����ָ��
 * DFS BFS�Ĵ�����㵥��һ��������д �����Ҫ���� ���QQȺ
 *
 * ���������л��� MinGW gcc8.3
 * ������ CLion2019.1
 * c��׼ c11
 * ������vs vcƽ̨������ ��Ϊ��֧��
 *
 *  ���������������
 *  ������4������ͼ�ж������Ϣ��
 *  a b c d
 *  ������5������ͼ�л�����Ϣ(��������8���ַ�) ��β ��ͷ Ȩֵ
 *  a b 1
 *  a d 1
 *  b c 1
 *  c a 1
 *  c d 1
 *  ������Ϣ
 *  [a] -> {1b -> 3d -> NULL}
 *  ������Ϣ
 *  [b] -> {2c -> NULL}
 *  ������Ϣ
 *  [c] -> {0a -> 3d -> NULL}
 *  ������Ϣ
 *  [d] -> {NULL}
 *  ����Ϊ2�Ķ��� c
 *  ��a�����޸�aa��鿴��� aa
 *  ����c�ĵ�һ���ڽӵ��λ�ú���Ϣ�� 0 aa
 *  -1
 *  ������Ϣ
 *  [aa] -> {1b -> 2d -> NULL}
 *  ������Ϣ
 *  [b] -> {NULL}
 *  ������Ϣ
 *  [d] -> {NULL}
 *  ɾ�������Ļ���ʣ 2��
 *  �µĲ��붥��e�Ƿ�ɹ�1
 *  ������v w��֮���Ȩֵweight
 *  1
 *  ���aa->e��һ�����Ƿ�ɹ�:1
 *  ������Ϣ
 *  [aa] -> {1b -> 2d -> 3e -> NULL}
 *  ������Ϣ
 *  [b] -> {NULL}
 *  ������Ϣ
 *  [d] -> {NULL}
 *  ������Ϣ
 *  [e] -> {NULL}
 *  ɾ��aa->d֮��Ļ��Ƿ�ɹ�:1
 *  ������Ϣ
 *  [aa] -> {1b -> 3e -> NULL}
 *  ������Ϣ
 *  [b] -> {NULL}
 *  ������Ϣ
 *  [d] -> {NULL}
 *  ������Ϣ
 *  [e] -> {NULL}
 * */
#include "adjmap.h"
int main(void) {
    ALGraph *g = (ALGraph *) malloc(sizeof(ALGraph));
    createGraph(g, 4, 5);
    display(g);
    printf("����Ϊ2�Ķ��� %s\n",getVex(g, 2));
    putVex(g, "a", "aa");
    printf("��a�����޸�aa��鿴��� %s\n", getVex(g, locateVex(g,"aa")));
    printf("����c�ĵ�һ���ڽӵ��λ�ú���Ϣ�� %d %s\n", fristAdjVex(g, "c"), getVex(g, fristAdjVex(g, "c")));
    printf("%d\n", nextAdjVex(g, "b", "c"));
    deleteVex(g,"c");
    display(g);
    printf("ɾ�������Ļ���ʣ %d��\n", g->arc);
    printf("�µĲ��붥��e�Ƿ�ɹ�%d\n",insertVex(g, "e"));
    printf("���aa->e��һ�����Ƿ�ɹ�:%d\n",insertArc(g, "aa", "e"));
    display(g);
    printf("ɾ��aa->d֮��Ļ��Ƿ�ɹ�:%d\n", deleteArc(g, "aa", "d"));
    display(g);
    return 0;
}