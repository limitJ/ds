//
// 数据结构 行逻辑链接顺序表稀疏矩阵存储压缩
// QQ群: 322085520
// Created by QQ 582521582 on 2019/3/4.
// 行逻辑稀疏矩阵存储 相比传统的稀疏矩阵存储压缩的如果查找存储某
// 一行 需要顺序查找 行逻辑矩阵则可以随意存取任意一行非零元素
//
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "rcsmatrix.h"
bool CreateSMatrix(RLSMatrix* M,int row,int col,int matrix[][col]){ // 创建稀疏矩阵M
    int count = 0;
    M->tu = 0;
    M->mu = row;
    M->nu = col;
    for (int i = 0; i < row; ++i) {
        M->rpos[i] = M->tu; //记录三元组矩阵中每一行出现的第一个非零元的所在的位置!
        for (int j = 0; j < col; ++j) {
            if (matrix[i][j] != 0) {
                M->tu++;
                M->data[count].i = i;
                M->data[count].j = j;
                M->data[count].element = matrix[i][j];
                count++;
            }
        }
    }
    return true;
}

void DestroySMatrix(RLSMatrix* M){ // 销毁稀疏矩阵M(使M为0行0列0个非零元素的矩阵)
    for (int i = 0; i < M->mu; ++i) {
        M->rpos[i] = 0;
    }
    M->mu=M->nu=M->tu=0;
}

void PrintSMatrix(RLSMatrix* M){ // 输出稀疏矩阵M
    printf("%d行%d列%d个非零元素。\n",M->mu,M->nu,M->tu);
    printf("行  列  元素值\n");
    for (int i = 0; i < M->tu; i++) {
        printf("%d   %d   %d\n",M->data[i].i,M->data[i].j,M->data[i].element);
    }
    for (int i = 0; i < M->mu; i++) {
        printf("第%d行的第一个非零元素是本矩阵第%d个元素\n",i,M->rpos[i]);
    }
}

void PrintSMatrix1(RLSMatrix* M){ // 按矩阵形式输出M
    Triple* p=M->data;
    for(int i=0;i<M->mu;i++){
        for(int j=0;j<M->nu;j++) {
            if (p->i == i && p->j == j) { // p指向非零元，且p所指元素为当前处理元素
                printf("%3d", p->element); // 输出p所指元素的值
                p++; // p指向下一个元素
            } else // p所指元素不是当前处理元素
                printf("%3d", 0); // 输出0
        }
        printf("\n");
    }
}

bool AddSMatrix(RLSMatrix *M, RLSMatrix *N, RLSMatrix *Q) { // 求稀疏矩阵的和Q=M+N
    int  p, q, tm, tn;
    if (M->mu != N->mu || M->nu != N->nu) {//矩阵行列不相等判断
        return false;
    }
    Q->mu = M->mu; // Q矩阵行数
    Q->nu = M->nu; // Q矩阵列数
    Q->tu = 0; // Q矩阵非零元素数初值
    for (int k = 0; k < M->mu; ++k) { // 对于每一行，k指示行号
        Q->rpos[k] = Q->tu; // Q矩阵第k行的第1个元素的位置
        p = M->rpos[k]; // p指示M矩阵第k行当前元素的序号
        q = N->rpos[k]; // q指示N矩阵第k行当前元素的序号
        if (k == M->mu-1) { // 是最后一行
            tm = M->tu; // tm，tn分别是p，q的上界
            tn = N->tu;
        } else {
            tm = M->rpos[k + 1];
            tn = N->rpos[k + 1];
        }
        while (p < tm && q < tn) { // M，N矩阵均有第k行元素未处理
            if (M->data[p].j == N->data[q].j) { // M矩阵当前元素的列=N矩阵当前元素的列
                if (M->data[p].element + N->data[q].element != 0) { // 和不为0，存入Q
                    Q->data[Q->tu] = M->data[p];
                    Q->data[Q->tu].element += N->data[q].element;
                    ++Q->tu;
                }
                p++;
                q++;
            } else if (M->data[p].j < N->data[q].j) { // M矩阵当前元素的列<N矩阵当前元素的列
                Q->data[Q->tu++] = M->data[p++]; // 将M的当前值赋给Q
            } else {// M矩阵当前元素的列>N矩阵当前元素的列
                Q->data[Q->tu++] = N->data[q++]; // 将N的当前值赋给Q
            }
        }
        while (p < tm) { // M矩阵还有第k行的元素未处理
            Q->data[Q->tu++] = M->data[p++]; // 将M的当前值赋给Q
        }
        while (q < tn) { // N矩阵还有k行的元素未处理
            Q->data[Q->tu++] = N->data[q++]; // 将N的当前值赋给Q
        }
    }
    if (Q->tu > MAX_SIZE) {
        return false;
    } else {
        return true;
    }
}

bool SubtSMatrix(RLSMatrix* M, RLSMatrix* N, RLSMatrix* Q){ // 求稀疏矩阵的差Q=M-N
    if (M->mu != N->mu || M->nu != N->nu) {
        return false;
    }
    for(int i = 0;i<N->tu;++i) { // 对于N的每一元素，其值乘以-1
        N->data[i].element*=-1;
    }
    AddSMatrix(M, N, Q); // Q=M+(-N)
    return true;
}

bool MultSMatrix(RLSMatrix* M,RLSMatrix* N,RLSMatrix* Q){ // 求稀疏矩阵乘积Q=M×N。算法5.3改
    int arow,brow = 0,p,q,ccol,ctemp[MAXRC+1], t = 0, tp = 0;
    if(M->nu!=N->mu || M->tu*N->tu == 0) { // 矩阵M的列数应和矩阵N的行数相等
        return false;
    }
    Q->mu=M->mu; // Q初始化
    Q->nu=N->nu;
    Q->tu=0;
    for(arow=0;arow<M->mu;++arow) { // 从M的第一行开始，到最后一行，arow是M的当前行
        for (ccol = 0; ccol < Q->nu; ++ccol) {
            ctemp[ccol] = 0; // Q的当前行的各列元素累加器清零 第一行各列元素清零
        }
        Q->rpos[arow] = Q->tu; // Q当前行的第1个元素位于上1行最后1个元素之后
        if (arow < M->mu - 1) {
            tp = M->rpos[arow + 1];//求得第一行的非零元个数从0开始
        } else if (arow == M->mu - 1) {//说明在最后一行了 直接访问剩下的非零元就可以
            tp = M->tu;
        }
        for (p = M->rpos[arow]; p < tp; ++p) { // 对M当前行中每一个非零元
            brow = M->data[p].j; // 找到对应元在N中的行号(M当前元的列号)
            if (brow < N->mu - 1) {
                t = N->rpos[brow + 1];
            } else if(brow == N->mu-1) {
                t = N->tu; // 给最后1行设界
            }
            for (q = N->rpos[brow]; q < t; ++q) {
                ccol = N->data[q].j; // 乘积元素在Q中列号
                ctemp[ccol] += M->data[p].element * N->data[q].element;
            }
        } // 求得Q中第arow行的非零元
        for(ccol=0;ccol<Q->nu;++ccol){ // 压缩存储该行非零元
            if(ctemp[ccol]!=0){
                Q->data[Q->tu].i=arow;
                Q->data[Q->tu].j=ccol;
                Q->data[Q->tu].element=ctemp[ccol];
                ++Q->tu;
            }
        }
    }
    return true;
}

void TransposeSMatrix(RLSMatrix* M,RLSMatrix* T) {// 求稀疏矩阵M的转置矩阵T
    int p,q,t,col,*num;
    num=(int *)malloc((M->nu+1)*sizeof(int));
    assert(num!=NULL);
    T->mu=M->nu;
    T->nu=M->mu;
    T->tu=M->tu;
    if(T->tu==0){
        return ;
    }
    for (col = 0; col < M->nu; ++col) {
        num[col]=0;  // 设初值
    }
    for (t = 0; t < M->tu; ++t) {
        ++num[M->data[t].j];
    } // 求M中每一列非零元个数 测试样例4 3
    T->rpos[0]=0;
    for (col = 1; col < M->nu; ++col) {
        T->rpos[col]=T->rpos[col-1]+num[col-1]; // 0 4
    } // 求M中第col中第一个非零元在T.data中的序号 将列向量转换成行向量
    for (col = 0; col <M->nu; ++col) {
        num[col] = T->rpos[col];
    }
    for(p=0;p<M->tu;++p){
        col=M->data[p].j;
        q=num[col];
        T->data[q].j=M->data[p].i;
        T->data[q].i=M->data[p].j;
        T->data[q].element=M->data[p].element;
        ++num[col]; //指示行中的向量每次用完就+1
    }
    free(num);
}
