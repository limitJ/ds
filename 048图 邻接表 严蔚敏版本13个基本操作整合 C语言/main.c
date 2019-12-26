#include "adjmap.h"
/*
 * ���ݽṹ
 * ͼ �ڽӱ�
 * ��ε�����ϵ�ȫ��13������ͼ�Ļ�������
 * ������ε�������ϵĲ���Ҫ��������ͼ ������ ����ͼ ������ �ǳ��ķ���
 * ���Ҵ󲿷ֲ����������� �ܶ����������ͬС�� û�б�Ҫȥ�ظ�ʵ��
 * ���Ϊ�˳���ı��ֻдһ��������
 * ���ϵĴ����Լ�̫���ֿ����� �����Լ�ʵ��һ��ͼ
 * ����ε����΢��Щ����ĵط�����
 * ��ADT�� ���˶�����firstarc�� ��������tailarc���ڷ�������Ĳ��� size���¼������ĳ���
 *
 * �������л��� ����ͨ�� �����гɹ�
 * ������:MinGW gcc version 8.3
 * ����ϵͳ��windows 10
 * IDE��CLion 2019.1
 * Cmake: 3.13
 *
 * ������vc vsƽ̨�����б����� ��֧��
 *
 * QQ 582521582
 * QQȺ 322085520
 * ����ˮƽ���� BUG�������� ��ӭ�Ķ���ָ�� �������ʺ�ָ�� ����ϵQQ���QQȺ����
 *
 * ���������������
 * ������4������ͼ�ж������Ϣ��
 * a b c d
 * ������5������ͼ�л�����Ϣ(��������8���ַ�) ��β ��ͷ Ȩֵ
 * a b 1
 * a d 1
 * b c 1
 * c a 1
 * c d 1
 * ������Ϣ
 * [a] -> {1b -> 3d -> NULL}
 * ������Ϣ
 * [b] -> {2c -> NULL}
 * ������Ϣ
 * [c] -> {0a -> 3d -> NULL}
 * ������Ϣ
 * [d] -> {NULL}
 * ����Ϊ2�Ķ��� c
 * ��a�����޸�aa��鿴��� aa
 * ����c�ĵ�һ���ڽӵ��λ�ú���Ϣ�� 0 aa
 * -1
 * ������Ϣ
 * [aa] -> {1b -> 2d -> NULL}
 * ������Ϣ
 * [b] -> {NULL}
 * ������Ϣ
 * [d] -> {NULL}
 * ɾ�������Ļ���ʣ 2��
 * �µĲ��붥��e�Ƿ�ɹ�1
 * ������v w��֮���Ȩֵweight
 * 1
 * ���aa->e��һ�����Ƿ�ɹ�:1
 * ������Ϣ
 * [aa] -> {1b -> 2d -> 3e -> NULL}
 * ������Ϣ
 * [b] -> {NULL}
 * ������Ϣ
 * [d] -> {NULL}
 * ������Ϣ
 * [e] -> {NULL}
 * ɾ��aa->d֮��Ļ��Ƿ�ɹ�:1
 * ������Ϣ
 * [aa] -> {1b -> 3e -> NULL}
 * ������Ϣ
 * [b] -> {NULL}
 * ������Ϣ
 * [d] -> {NULL}
 * ������Ϣ
 * [e] -> {NULL}
 * ������8������ͼ�ж������Ϣ��
 * v1 v2 v3 v4 v5 v6 v7 v8
 * ������9������ͼ�л�����Ϣ(��������8���ַ�) ��β ��ͷ Ȩֵ
 * v1 v2 1
 * v1 v3 1
 * v2 v4 1
 * v2 v5 1
 * v4 v8 1
 * v5 v8 1
 * v3 v6 1
 * v3 v7 1
 * v6 v7 1
 * ������Ϣ
 * [v1] -> {1v2 -> 2v3 -> NULL}
 * ������Ϣ
 * [v2] -> {3v4 -> 4v5 -> NULL}
 * ������Ϣ
 * [v3] -> {5v6 -> 6v7 -> NULL}
 * ������Ϣ
 * [v4] -> {7v8 -> NULL}
 * ������Ϣ
 * [v5] -> {7v8 -> NULL}
 * ������Ϣ
 * [v6] -> {6v7 -> NULL}
 * ������Ϣ
 * [v7] -> {NULL}
 * ������Ϣ
 * [v8] -> {NULL}
 * DFS������ȱ���ͼ
 * v1 v2 v4 v8 v5 v3 v6 v7
 * BFS������ȱ���ͼ
 * v1 v2 v3 v4 v5 v6 v7 v8
 *
 * */
int main(void) {
    ALGraph *g = (ALGraph *) malloc(sizeof(ALGraph));
    createGraph(g, 4, 5);
    display(g);
    printf("����Ϊ2�Ķ��� %s\n",getVex(g, 2));
    putVex(g, "a", "aa");
    printf("��a�����޸�aa��鿴��� %s\n", getVex(g, locateVex(g,"aa")));
    printf("����c�ĵ�һ���ڽӵ��λ�ú���Ϣ�� %d %s\n", fristAdjVex(g, "c"), getVex(g, fristAdjVex(g, "c")));
    printf("b������c����һ���ڵ���Ϣ����ǣ�%d\n", nextAdjVex(g, "b", "c"));
    deleteVex(g,"c");
    display(g);
    printf("ɾ�������Ļ���ʣ %d��\n", g->arc);
    printf("�µĲ��붥��e�Ƿ�ɹ�%d\n",insertVex(g, "e"));
    printf("���aa->e��һ�����Ƿ�ɹ�:%d\n",insertArc(g, "aa", "e"));
    display(g);
    printf("ɾ��aa->d֮��Ļ��Ƿ�ɹ�:%d\n", deleteArc(g, "aa", "d"));
    display(g);
    ALGraph *graph = (ALGraph *) malloc(sizeof(ALGraph));
    createGraph(graph, 8, 9);
    display(graph);
    DFSTreverse(graph);
    BFSTreverse(graph);
    free(g);
    free(graph);
    return 0;
}