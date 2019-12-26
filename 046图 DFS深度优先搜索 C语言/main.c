/*
 * ͼ DFS ������ȱ���
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
    ������ȱ��������
    v1 v2 v4 v8 v5 v3 v6 v7
 * */
#include "adjmap.h"
bool visited[MAX_VEX_NUM] = {false};
void DFSTreverse(ALGraph* G);
void DFS(ALGraph* G,int v);
int main(void) {
    ALGraph *g = (ALGraph *) malloc(sizeof(ALGraph));
    createGraph(g, 8, 8);
    printf("������ȱ��������\n");
    DFSTreverse(g);
    printf("\n");
    return 0;
}

void DFSTreverse(ALGraph* G){
    for (int v = 0;v<G->vex;v++) {
        if (!visited[v]) {
            DFS(G, v);
        }
    }
}
void DFS(ALGraph* G,int v){
    visited[v] = true;
    printf("%s ", getVex(G, v));
    for (int w = fristAdjVex(G,getVex(G,v));w>=0;w = nextAdjVex(G,getVex(G,v),getVex(G,w))) {
        if (!visited[w]) {
            DFS(G, w);
        }
    }
}