//
// Created by QQ 582521582 on 2019/2/24.
// QQ群: 322085520
// 三元组稀疏矩阵的基本操作
#include <stdio.h>
#include <stdlib.h>
#include "sparsematrix.h"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "missing_default_case"
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wlogical-op-parentheses"
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

void DestroySMatrix(TSMatrix* tsm){ // 销毁稀疏矩阵M
    tsm->mu=tsm->nu=tsm->tu=0;
}

void PrintSMatrix(TSMatrix* TSM){ // 输出稀疏矩阵M
    int i;
    printf("%d行%d列%d个非零元素。\n",TSM->mu,TSM->nu,TSM->tu);
    printf("行  列  元素值\n");
    for(i=0;i<TSM->tu;i++)
        printf("%d%4d%6d\n",TSM->data[i].i,TSM->data[i].j,TSM->data[i].element);
}
void PrintSMatrix1(TSMatrix* M){ // 按矩阵形式输出M
    int i,j,k=0;
    Triple *p=M->data;
    for(i=0;i<M->mu;i++){
        for(j=0;j<M->nu;j++)
            if(k<M->tu&&p->i==i&&p->j==j){ // p指向非零元，且p所指元素为当前处理元素
                printf("%3d",p->element); // 输出p所指元素的值
                p++; // p指向下一个元素
                k++; // 计数器+1
            }
            else { // p所指元素不是当前处理元素
                printf("%3d", 0); // 输出0
            }
        printf("\n");
    }
}

void CopySMatrix(TSMatrix* M,TSMatrix* T){ // 由稀疏矩阵M复制得到T
    *T = *M;
}

int comp(int c1,int c2){ // AddSMatrix函数要用
    if(c1<c2) {
        return -1;
    }
    if(c1==c2) {
        return 0;
    }
    return 1;
}

bool AddSMatrix(TSMatrix* M,TSMatrix* N,TSMatrix* Q){ // 求稀疏矩阵的和Q=M+N
    int m=0,n=0,q=0;
    if(M->mu!=N->mu||M->nu!=N->nu) { // M、N两稀疏矩阵行或列数不同
        puts("矩阵行列不一致,无法进行四则运算操作");
        return false;
    }
    Q->mu=M->mu;
    Q->nu=M->nu;
    while(m<M->tu&&n<N->tu){ // 矩阵M和N的元素都没处理完
        switch(comp(M->data[m].i,N->data[n].i)){
            case -1:
                Q->data[q].i=M->data[m].i; // 将矩阵M的当前元素值赋给矩阵Q
                Q->data[q].j = M->data[m].j;
                Q->data[q].element = M->data[m].element;
                q++;
                m++;
                break;
            case  0:
                switch(comp(M->data[m].j,N->data[n].j)){ // M、N矩阵当前元素的行相等,继续比较列
                    case -1:
                        Q->data[q].i=M->data[m].i; // 将矩阵M的当前元素值赋给矩阵Q
                        Q->data[q].j = M->data[m].j;
                        Q->data[q].element = M->data[m].element;
                        q++;
                        m++;
                        break;
                    case  0:
                        Q->data[q].i = M->data[m].i;
                        Q->data[q].j = M->data[m].j;
                        Q->data[q].element =M->data[m].element+N->data[n++].element; // 矩阵M、N的当前元素值求和并赋给矩阵Q
                        m++;
                        q++;
                        break;
                    case  1:
                        Q->data[q].i=N->data[n].i; // 将矩阵M的当前元素值赋给矩阵Q
                        Q->data[q].j = N->data[n].j;
                        Q->data[q].element = N->data[n].element;
                        q++;
                        n++;
                        break;

                }
                break;
            case  1:
                Q->data[q].i=N->data[n].i; // 将矩阵M的当前元素值赋给矩阵Q
                Q->data[q].j = N->data[n].j;
                Q->data[q].element = N->data[n].element;
                q++;
                n++;
                break;
            }
    }
    while(m<M->tu) { // 矩阵N的元素全部处理完毕
        Q->data[q].i = M->data[m].i;
        Q->data[q].j = M->data[m].j;
        Q->data[q].element =M->data[m].element+N->data[n++].element; // 矩阵M、N的当前元素值求和并赋给矩阵Q
        m++;
        q++;
    }
    while(n<N->tu) { // 矩阵M的元素全部处理完毕
        Q->data[q].i=N->data[n].i; // 将矩阵M的当前元素值赋给矩阵Q
        Q->data[q].j = N->data[n].j;
        Q->data[q].element = N->data[n].element;
        q++;
        n++;
    }
    Q->tu=q; // 矩阵Q的非零元素个数
    if(q>MAXSIZE) { // 非零元素个数太多
        return false;
    }
    return true;
}

bool SubtSMatrix(TSMatrix* M,TSMatrix* N,TSMatrix* Q){ // 求稀疏矩阵的差Q=M-N
    int i;
    for (i = 1; i <= N->tu; i++) {
        N->data[i].element*=-1;
    }
    AddSMatrix(M,N,Q);
    return true;
}

void TransposeSMatrix(TSMatrix* M,TSMatrix* T){ // 求稀疏矩阵M的转置矩阵T。
    int q = 0;
    T->mu=M->nu;
    T->nu=M->mu;
    T->tu=M->tu;
    if(T->tu!=0){
        for(int col=0;col<M->nu;++col){
            for(int p=0;p<M->tu;++p) {
                if (M->data[p].j == col) {
                    T->data[q].i = M->data[p].j;
                    T->data[q].j = M->data[p].i;
                    T->data[q].element = M->data[p].element;
                    ++q;
                }
            }
        }
    }
}

bool MultSMatrix(TSMatrix* M,TSMatrix* N,TSMatrix* Q){ // 求稀疏矩阵的乘积Q=M×N
    int i,j;
    int *Nc,*Tc;
    TSMatrix* T = (TSMatrix*)malloc(sizeof(TSMatrix)); // 临时矩阵
    printf("%d %d\n", M->nu, N->mu);
    if (M->nu != N->mu) {
        return false;
    }
    T->nu=M->mu; // 临时矩阵T是Q的转秩矩阵
    T->mu=N->nu;
    T->tu=0;
    Nc=(int*)malloc((N->mu)*sizeof(int)); // Nc为矩阵N一列的临时数组(非压缩,不用)
    Tc=(int*)malloc((M->nu)*sizeof(int)); // Tc为矩阵T一行的临时数组(非压缩,不用)
    if(!Nc||!Tc) { // 创建临时数组不成功
        exit(-1);
    }
    for(i=0;i<N->nu;i++){ // 对于N的每一列
        for(j=0;j<N->mu;j++){
            Nc[j]=0; // 矩阵Nc的初值为0
        }
        for(j=0;j<M->mu;j++) {
            Tc[j] = 0; // 临时数组Tc的初值为0

        }
        for(j=0;j<N->tu;j++) { // 对于N的每一个非零元素
            if (N->data[j].j == i) {// 属于第i列
                Nc[N->data[j].i] = N->data[j].element; // 根据其所在行将其元素值赋给相应的Nc
            }
        }
        for(j=0;j<M->tu;j++) { // 对于M的每一个值
            Tc[M->data[j].i] += M->data[j].element * Nc[M->data[j].j]; // Tc中存N的第i列与M相乘的结果
        }
        for(j=0;j<M->mu;j++) {
            if (Tc[j] != 0) {
                T->data[T->tu].element = Tc[j];
                T->data[T->tu].i = i;
                T->data[T->tu].j = j;
                T->tu++;
            }
        }
    }
    if (T->tu > MAXSIZE) {
        return false;
    } // 非零元素个数太多
    TransposeSMatrix(T,Q); // 将T的转秩赋给Q
    DestroySMatrix(T);
    free(Nc);
    free(Tc);
    return true;
}

#pragma clang diagnostic pop