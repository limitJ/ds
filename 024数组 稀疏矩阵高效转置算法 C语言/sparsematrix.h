//
// Created by QQ 582521582 on 2019/2/24.
//

#ifndef SPARSEMATRIX_SPARSEMATRIX_H
#define SPARSEMATRIX_SPARSEMATRIX_H

#include <stdbool.h>
#define MAXSIZE 1024
typedef struct Triple{
    int i;//非零元行下表与列下表
    int j;
    int element;//非零元元素
}Triple;
typedef struct TSMatrix{
    Triple data[MAXSIZE+1];
    int mu;//矩阵的行数
    int nu;//矩阵的列数
    int tu;//非零元个数
}TSMatrix;
bool CreateSMatrix(TSMatrix* TSM,int matrix[][7],int col,int row);
void PrintSMatrix(TSMatrix* TSM);
void FastTransposeSMatrix(TSMatrix* M,TSMatrix* T);
#endif //SPARSEMATRIX_SPARSEMATRIX_H
