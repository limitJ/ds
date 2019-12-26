/*
 * ͼ BFS ������ȱ���
 * QQ 582521582
 * QQȺ 322085520
 * ����ˮƽ���� ������������ ��ӭ����ָ��
 * ���������л��� MinGW gcc8.3
 * ������ CLion2019.1
 * c��׼ c11
 * ������vs vcƽ̨������ ��֧��
 * ���������������
 * ������8������ͼ�ж������Ϣ��
    v1 v2 v3 v4 v5 v6 v7 v8
    ������8������ͼ�л�����Ϣ(��������8���ַ�) ��β ��ͷ Ȩֵ
    v1 v2 1
    v1 v3 1
    v2 v4 1
    v2 v5 1
    v5 v8 1
    v4 v8 1
    v3 v6 1
    v3 v7 1
    ��ȶ����ȱ��������
    v1 v2 v3 v4 v5 v6 v7 v8
 * */
#include "adjmap.h"
#include "queue.h"
bool visited[MAX_VEX_NUM] = {false};
void BFS(ALGraph* G);
int main(void) {
    ALGraph *g = (ALGraph *) malloc(sizeof(ALGraph));
    createGraph(g, 8, 8);//
    printf("��ȶ����ȱ��������\n");
    BFS(g);
    printf("\n");
    return 0;
}
void BFS(ALGraph* G){
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    initQueue(queue);
    for (int v = 0; v < G->vex; ++v) {
        if (visited[v] == false) {//��û�з��ʹ�
            visited[v] = true;
            printf("%s ", getVex(G, v));
        }
        poll(queue, &G->vexarrs[v]);
        while (!isEmpty(queue)) {
            pop(queue);
            char* ch = getVex(G,v);
            for (int w = fristAdjVex(G, ch); w >= 0; w = nextAdjVex(G, getVex(G, v), getVex(G, w))) {
                if (visited[v] == false) {//��û�з��ʹ�
                    visited[v] = true;
                    printf("%s ", getVex(G, w));
                    poll(queue, &G->vexarrs[w]);
                }
            }
        }
    }
}