//
// Created by QQ 582521582 on 2019/2/24.
// QQ群: 322085520
// 三元组稀疏矩阵 置换算法
#include <stdio.h>
#include <stdlib.h>
#include "sparsematrix.h"
bool CreateSMatrix(TSMatrix* TSM,int matrix[][7],int col,int row){ // 创建稀疏矩阵TSM
    int count = 0;
    TSM->mu = col;
    TSM->nu = row;
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            if (matrix[i][j] != 0) {
                TSM->tu++;
                if (TSM->tu > MAXSIZE) {
                    return false;
                }
                TSM->data[count].i=i;
                TSM->data[count].j=j;
                TSM->data[count].element=matrix[i][j];
                count++;
            }
        }
    }
    return true;
}

void PrintSMatrix(TSMatrix* TSM){ // 输出稀疏矩阵M
    int i;
    printf("%d行%d列%d个非零元素。\n",TSM->mu,TSM->nu,TSM->tu);
    printf("行  列  元素值\n");
    for(i=0;i<TSM->tu;i++)
        printf("%d%4d%6d\n",TSM->data[i].i,TSM->data[i].j,TSM->data[i].element);
}
void FastTransposeSMatrix(TSMatrix* M,TSMatrix* T){ // 快速求稀疏矩阵M的转置矩阵T。
    int q=0,col = 0;
    int* num=(int *)malloc(M->nu*sizeof(int)); // 存M每列(T每行)非零元素个数)
    int* cpot=(int *)malloc(M->nu*sizeof(int)); // 存T每行的下1个非零元素的存储位置)
    T->mu=M->nu; // 给T的行、列数与非零元素个数赋值
    T->nu=M->mu;
    T->tu=M->tu;
    if(T->tu!=0) { // 是非零矩阵{
        for (col = 0; col < M->nu; ++col) {
            num[col] = 0; // 计数器初值设为0
            cpot[col] = 0;
        }
    }
    for(int t=0;t<M->tu;++t) { // 求M中每一列含非零元素个数
        ++num[M->data[t].j];
    }
    for(col=1;col<M->nu;++col) {
        cpot[col] = cpot[col-1] + num[col-1]; // 求T的第col行的第1个非零元在T.data中的序号
        //第一个非零元的位置由num确定 比如num[0]有2个元素!那么则如果j是1 则说明跳过0列中的元素 位置就是变成了T所在的位置
    }
    for(int p=0;p<M->tu;++p){ // 从M的第0个元素开始
        col=M->data[p].j; // 求得在M中的列数
        q=cpot[col]; // q指示M当前的元素在T中的序号
        T->data[q].i=M->data[p].j;
        T->data[q].j=M->data[p].i;
        T->data[q].element=M->data[p].element;
        ++cpot[col]; // T第col行的下1个非零元在T.data中的序号
    }
    free(num);
    free(cpot);
}