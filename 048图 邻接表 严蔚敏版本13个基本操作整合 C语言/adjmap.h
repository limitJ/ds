//
// Created by QQ 582521582 on 2019/5/17.
//

#ifndef ADJMAP_ADJMAP_H
#define ADJMAP_ADJMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#define  MAX_VEX_NUM 32 //������Ϣ ���32��
#define throwException(e) fputs(e,stderr)
typedef struct ArcNode{
    int index;//��ʾ�����������±��λ��
    int weight;//Ȩֵ �����ͼĬ��Ϊ1
    struct ArcNode* nextarc;
}ArcNode;
typedef struct {
    char vexinfo[8];//��Ŷ�����Ϣ
    ArcNode* firstarc;//������
    ArcNode* tailarc;//��Ϊÿ�ζ����ں������ ��������ά��һ��βָ�� �������
    int size;
}AdjList[MAX_VEX_NUM];
typedef struct {
    AdjList vexarrs;
    int vex;//��������
    int arc;//������
}ALGraph;
int locateVex(ALGraph* G,char vexInfo[8]);
void createGraph(ALGraph* G,int vex,int arc);
void display(ALGraph *G);
void addarcnode(AdjList adjList,ArcNode* arcNode);
char* getVex(ALGraph* G,int index);
bool putVex(ALGraph* G,char v[8],char newv[8]);
int fristAdjVex(ALGraph* G, char v[8]);
int nextAdjVex(ALGraph* G, char v[8],char w[8]);
bool insertVex(ALGraph* G,char v[8]);
bool deleteVex(ALGraph* G,char v[8]);
bool insertArc(ALGraph* G,char v[8],char w[8]);
bool deleteArc(ALGraph* G, char v[8],char w[8]);
void BFSTreverse(ALGraph* G);
void DFSTreverse(ALGraph* G);
void DFS(ALGraph* G,int v,bool visited[MAX_VEX_NUM]);
#endif //ADJMAP_ADJMAP_H
