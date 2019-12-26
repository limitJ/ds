#include <stdio.h>
#include <stdlib.h>
#include "sparsematrix.h"
#define len(arr) sizeof(arr)/sizeof(arr[0])
int main(void) {
    TSMatrix *A = (TSMatrix *) malloc(sizeof(TSMatrix));
    int matrix[6][7]={
            {0,12,9,0,0,0,0},
            {0,0,0,0,0,0,0},
            {-3,0,0,0,0,14,0},
            {0,0,24,0,0,0,0},
            {0,18,0,0,0,0,0},
            {15,0,0,-7,0,0,0}
    };
    int matrix2[6][7]={
            {0,2,9,0,0,0,0},
            {0,2,0,0,8,0,0},
            {5,0,0,0,0,11,0},
            {1,0,24,0,0,0,0},
            {0,18,0,0,0,0,0},
            {10,0,0,53,0,0,0}
    };
    printf("创建稀疏矩阵A: ");
    CreateSMatrix(A,matrix,len(matrix),len(matrix[0]));
    PrintSMatrix(A);
    printf("输出原型矩阵A: \n");
    PrintSMatrix1(A);
    printf("由矩阵A复制矩阵B:\n");
    TSMatrix *B = (TSMatrix *) malloc(sizeof(TSMatrix));
    CopySMatrix(A,B);
    PrintSMatrix(B);
    DestroySMatrix(B);
    printf("销毁矩阵B后:\n");
    PrintSMatrix(B);
    printf("创建矩阵B2:(与矩阵A的行、列数相同，行、列分别为%d,%d)\n",A->mu,A->nu);
    TSMatrix* B1 = (TSMatrix *) malloc(sizeof(TSMatrix));
    TSMatrix* C1 = (TSMatrix *) malloc(sizeof(TSMatrix));
    CreateSMatrix(B1,matrix2,len(matrix2),len(matrix2[0]));
    printf("输出矩阵B1\n");
    PrintSMatrix(B1);
    AddSMatrix(A,B1,C1);
    printf("矩阵C1(A+B1):\n");
    PrintSMatrix1(C1);
    TSMatrix* C2 = (TSMatrix *) malloc(sizeof(TSMatrix));
    SubtSMatrix(A,B1,C2);
    printf("矩阵C2(A-B1):\n");
    PrintSMatrix1(C2);
    TSMatrix* C3 = (TSMatrix *) malloc(sizeof(TSMatrix));
    TransposeSMatrix(A,C3);
    printf("矩阵C3(A的转置):\n");
    PrintSMatrix1(C3);
    int matrix3[6][7]={
            {0,12,9,0,0,0,0},
            {0,0,0,0,0,0,0},
            {3,0,0,0,0,14,0},
            {0,0,24,0,0,0,0},
            {0,18,0,0,0,0,0},
            {15,0,0,7,0,0,0}
    };
    int matrix4[7][7]={
            {0,12,9,0,0,0,0},
            {0,0,0,0,-5,0,0},
            {3,0,0,0,0,14,0},
            {0,0,24,0,0,0,0},
            {0,18,0,0,0,0,0},
            {15,0,0,7,0,0,0},
            {10,1,0,8,0,0,2}
    };
    TSMatrix *A1 = (TSMatrix *) malloc(sizeof(TSMatrix));
    CreateSMatrix(A1, matrix3, len(matrix3), len(matrix3[0]));
    TSMatrix *B2 = (TSMatrix *) malloc(sizeof(TSMatrix));
    CreateSMatrix(B2, matrix4, len(matrix4), len(matrix4[0]));
    TSMatrix* C4 = (TSMatrix *) malloc(sizeof(TSMatrix));
    MultSMatrix(A1,B2,C4);
    printf("矩阵C4(A1×B2):\n");
    PrintSMatrix(C4);
    return 0;
}