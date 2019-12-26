/*
 *
 * 块链稀疏矩阵
 * 运行环境MinGW8.1  gcc8.1
 * 请勿在其他编译器下运行 尤其是VC
 * c最低支持标准 c11
 * cmake版本 1.31
 * by QQ 582521582
 * QQ群 322085520
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include "rcsmatrix.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-designator"
#define len(arr) sizeof(arr)/sizeof(arr[0])
#define newObject(Object) (Object *)malloc(sizeof(Object))
int main(void) {
    RLSMatrix* A = newObject(RLSMatrix);
    int matrix1[4][2] = {
            [0]{[0] = 0,[1] = 2},
            [1]{[0] = 1,[1] = 0},
            [2]{[0] =-2,[1] = 4},
            [3]{[0] = 0,[1] = 0},
    };
    int matrix2[4][2] = {
            [0]{[0] = 1,[1] = 3},
            [1]{[0] = 1,[1] = 0},
            [2]{[0] =-2,[1] = 2},
            [3]{[0] = 1,[1] = 0},
    };
    printf("创建矩阵A: ");
    CreateSMatrix(A,len(matrix1),len(matrix1[0]),matrix1);
    PrintSMatrix(A);
    PrintSMatrix1(A);
    printf("销毁矩阵A后:\n");
    DestroySMatrix(A);
    PrintSMatrix1(A);
    printf("创建矩阵M,N:(M,N矩阵的行、列数相同，)\n");
    RLSMatrix* M = newObject(RLSMatrix);
    RLSMatrix* N = newObject(RLSMatrix);
    CreateSMatrix(M,len(matrix1),len(matrix1[0]),matrix1);
    CreateSMatrix(N,len(matrix2),len(matrix2[0]),matrix2);
    RLSMatrix* Q = newObject(RLSMatrix);
    AddSMatrix(M,N,Q);
    printf("矩阵Q(M+N):\n");
    PrintSMatrix(Q);
    PrintSMatrix1(Q);
    printf("矩阵Q(M-N):\n");
    RLSMatrix *Q2 = newObject(RLSMatrix);
    SubtSMatrix(M,N,Q2);
    PrintSMatrix(Q2);
    PrintSMatrix1(Q2);
    RLSMatrix *N2 = newObject(RLSMatrix);//
    CreateSMatrix(N2,len(matrix2),len(matrix2[0]),matrix2);
    PrintSMatrix(N2);
    printf("N的置换矩阵T:\n");
    RLSMatrix *T = newObject(RLSMatrix);
    TransposeSMatrix(N2,T);//这里不要拿N矩阵测试 因为N矩阵已经在sub运算中改变了值
    PrintSMatrix(T);
    PrintSMatrix1(T);
    printf("矩阵Q3(M3×N3):\n");
    RLSMatrix* M3 = newObject(RLSMatrix);
    RLSMatrix* N3 = newObject(RLSMatrix);
    int matrix3[4][2] = {
            [0]{[0] = 0,[1] = 2},
            [1]{[0] = 1,[1] = 0},
            [2]{[0] =-2,[1] = 4},
            [3]{[0] = 0,[1] = 0},
    };
    int matrix4[2][3] = {
            [0]{[0] = 1,[1] = 3,[2] = 0},
            [1]{[0] = 2,[1] = 3,[2] = 2}
    };
    CreateSMatrix(M3,len(matrix3),len(matrix3[0]),matrix3);
    CreateSMatrix(N3,len(matrix4),len(matrix4[0]),matrix4);
    RLSMatrix* Q3 = newObject(RLSMatrix);
    MultSMatrix(M3,N3,Q3);
    PrintSMatrix(Q3);
    PrintSMatrix1(Q3);
    printf("Done!\n");
    return 0;
}
#pragma clang diagnostic pop