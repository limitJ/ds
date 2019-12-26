//
// 数据结构 行逻辑链接顺序表稀疏矩阵存储压缩
// QQ群: 322085520
// Created by QQ 582521582 on 2019/3/4.
// 行逻辑稀疏矩阵存储 相比传统的稀疏矩阵存储压缩的如果查找存储某
// 一行 需要顺序查找 行逻辑矩阵则可以随意存取任意一行非零元素
//
#ifndef RCSRTSMATRIX_RCSMATRIX_H
#define RCSRTSMATRIX_RCSMATRIX_H

#include <stdbool.h>
#include <assert.h>
#define MAX_SIZE 128//最大非零元数
#define MAXRC 32 //最大行列数
typedef struct{
    int i;//行坐标
    int j;//列坐标
    int element;//非零元素
}Triple;
typedef struct{
    Triple data[MAX_SIZE];//非零元三元组表
    int rpos[MAXRC]; //各行第一个非零元的位置表
    int mu;//行数
    int nu;//列数
    int tu;//非零元数
}RLSMatrix;
bool CreateSMatrix(RLSMatrix* M,int row,int col,int matrix[][col]);
void DestroySMatrix(RLSMatrix* M);
void PrintSMatrix(RLSMatrix* M);
void PrintSMatrix1(RLSMatrix* M);
bool AddSMatrix(RLSMatrix* M,RLSMatrix* N,RLSMatrix* Q);
bool SubtSMatrix(RLSMatrix* M, RLSMatrix* N, RLSMatrix* Q);
void TransposeSMatrix(RLSMatrix* M,RLSMatrix* T);
bool MultSMatrix(RLSMatrix* M,RLSMatrix* N,RLSMatrix* Q);
#endif //RCSRTSMATRIX_RCSMATRIX_H
