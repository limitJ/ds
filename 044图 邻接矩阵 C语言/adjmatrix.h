//
// Created by QQ 582521582 on 2019/5/16.
// 数据结构 图
// 邻接矩阵表示法
// QQ群 322085520
//

#ifndef ADJMATRIX_ADJMATRIX_H
#define ADJMATRIX_ADJMATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#define len(arr) (int)(sizeof(arr)/sizeof(arr[0]))
#define MAX_VEX_NUM 16 //最大节点个数
#define throwException(e) fputs(e,stderr)
enum GraphKind {DG,DN,UDG,UDN};//分部表示有向图 有向网 无向图 无向网
//有向网 无向网的代表的意思是每个弧/边都有各自的权值
typedef struct {
    int adj;//存放顶点的值 无向网或有向网里面默认存储的无穷 在计算机里 为我们用0XFFFFFFF代替
    char* info;//存放额外的信息 可以不用
}AdjMatrix[MAX_VEX_NUM][MAX_VEX_NUM];

typedef struct {
    char vexarrs[MAX_VEX_NUM][16];//邻接矩阵顶点向量
    AdjMatrix adjmat;//邻接矩阵存储
    int vex;//顶点数
    int arc;//弧数
    enum GraphKind kind;//图的类型
}AMGraph;
void CreateGraph(AMGraph* G);
int LocateVex(AMGraph* G,char u[16]);
void CreateDG(AMGraph* G);
void CreateDN(AMGraph* G);
void CreateUDG(AMGraph* G);
void CreateUDN(AMGraph* G);
void Display(AMGraph* G);
void InsertVex(AMGraph* G,char v[16]);
bool InsertArc(AMGraph* G,char v[16],char w[16]);
void DestroyGraph(AMGraph* G);
#endif //ADJMATRIX_ADJMATRIX_H
