//
// ���ݽṹ ���߼�����˳���ϡ�����洢ѹ��
// QQȺ: 322085520
// Created by QQ 582521582 on 2019/3/4.
// ���߼�ϡ�����洢 ��ȴ�ͳ��ϡ�����洢ѹ����������Ҵ洢ĳ
// һ�� ��Ҫ˳����� ���߼���������������ȡ����һ�з���Ԫ��
//
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "rcsmatrix.h"
bool CreateSMatrix(RLSMatrix* M,int row,int col,int matrix[][col]){ // ����ϡ�����M
    int count = 0;
    M->tu = 0;
    M->mu = row;
    M->nu = col;
    for (int i = 0; i < row; ++i) {
        M->rpos[i] = M->tu; //��¼��Ԫ�������ÿһ�г��ֵĵ�һ������Ԫ�����ڵ�λ��!
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

void DestroySMatrix(RLSMatrix* M){ // ����ϡ�����M(ʹMΪ0��0��0������Ԫ�صľ���)
    for (int i = 0; i < M->mu; ++i) {
        M->rpos[i] = 0;
    }
    M->mu=M->nu=M->tu=0;
}

void PrintSMatrix(RLSMatrix* M){ // ���ϡ�����M
    printf("%d��%d��%d������Ԫ�ء�\n",M->mu,M->nu,M->tu);
    printf("��  ��  Ԫ��ֵ\n");
    for (int i = 0; i < M->tu; i++) {
        printf("%d   %d   %d\n",M->data[i].i,M->data[i].j,M->data[i].element);
    }
    for (int i = 0; i < M->mu; i++) {
        printf("��%d�еĵ�һ������Ԫ���Ǳ������%d��Ԫ��\n",i,M->rpos[i]);
    }
}

void PrintSMatrix1(RLSMatrix* M){ // ��������ʽ���M
    Triple* p=M->data;
    for(int i=0;i<M->mu;i++){
        for(int j=0;j<M->nu;j++) {
            if (p->i == i && p->j == j) { // pָ�����Ԫ����p��ָԪ��Ϊ��ǰ����Ԫ��
                printf("%3d", p->element); // ���p��ָԪ�ص�ֵ
                p++; // pָ����һ��Ԫ��
            } else // p��ָԪ�ز��ǵ�ǰ����Ԫ��
                printf("%3d", 0); // ���0
        }
        printf("\n");
    }
}

bool AddSMatrix(RLSMatrix *M, RLSMatrix *N, RLSMatrix *Q) { // ��ϡ�����ĺ�Q=M+N
    int  p, q, tm, tn;
    if (M->mu != N->mu || M->nu != N->nu) {//�������в�����ж�
        return false;
    }
    Q->mu = M->mu; // Q��������
    Q->nu = M->nu; // Q��������
    Q->tu = 0; // Q�������Ԫ������ֵ
    for (int k = 0; k < M->mu; ++k) { // ����ÿһ�У�kָʾ�к�
        Q->rpos[k] = Q->tu; // Q�����k�еĵ�1��Ԫ�ص�λ��
        p = M->rpos[k]; // pָʾM�����k�е�ǰԪ�ص����
        q = N->rpos[k]; // qָʾN�����k�е�ǰԪ�ص����
        if (k == M->mu-1) { // �����һ��
            tm = M->tu; // tm��tn�ֱ���p��q���Ͻ�
            tn = N->tu;
        } else {
            tm = M->rpos[k + 1];
            tn = N->rpos[k + 1];
        }
        while (p < tm && q < tn) { // M��N������е�k��Ԫ��δ����
            if (M->data[p].j == N->data[q].j) { // M����ǰԪ�ص���=N����ǰԪ�ص���
                if (M->data[p].element + N->data[q].element != 0) { // �Ͳ�Ϊ0������Q
                    Q->data[Q->tu] = M->data[p];
                    Q->data[Q->tu].element += N->data[q].element;
                    ++Q->tu;
                }
                p++;
                q++;
            } else if (M->data[p].j < N->data[q].j) { // M����ǰԪ�ص���<N����ǰԪ�ص���
                Q->data[Q->tu++] = M->data[p++]; // ��M�ĵ�ǰֵ����Q
            } else {// M����ǰԪ�ص���>N����ǰԪ�ص���
                Q->data[Q->tu++] = N->data[q++]; // ��N�ĵ�ǰֵ����Q
            }
        }
        while (p < tm) { // M�����е�k�е�Ԫ��δ����
            Q->data[Q->tu++] = M->data[p++]; // ��M�ĵ�ǰֵ����Q
        }
        while (q < tn) { // N������k�е�Ԫ��δ����
            Q->data[Q->tu++] = N->data[q++]; // ��N�ĵ�ǰֵ����Q
        }
    }
    if (Q->tu > MAX_SIZE) {
        return false;
    } else {
        return true;
    }
}

bool SubtSMatrix(RLSMatrix* M, RLSMatrix* N, RLSMatrix* Q){ // ��ϡ�����Ĳ�Q=M-N
    if (M->mu != N->mu || M->nu != N->nu) {
        return false;
    }
    for(int i = 0;i<N->tu;++i) { // ����N��ÿһԪ�أ���ֵ����-1
        N->data[i].element*=-1;
    }
    AddSMatrix(M, N, Q); // Q=M+(-N)
    return true;
}

bool MultSMatrix(RLSMatrix* M,RLSMatrix* N,RLSMatrix* Q){ // ��ϡ�����˻�Q=M��N���㷨5.3��
    int arow,brow = 0,p,q,ccol,ctemp[MAXRC+1], t = 0, tp = 0;
    if(M->nu!=N->mu || M->tu*N->tu == 0) { // ����M������Ӧ�;���N���������
        return false;
    }
    Q->mu=M->mu; // Q��ʼ��
    Q->nu=N->nu;
    Q->tu=0;
    for(arow=0;arow<M->mu;++arow) { // ��M�ĵ�һ�п�ʼ�������һ�У�arow��M�ĵ�ǰ��
        for (ccol = 0; ccol < Q->nu; ++ccol) {
            ctemp[ccol] = 0; // Q�ĵ�ǰ�еĸ���Ԫ���ۼ������� ��һ�и���Ԫ������
        }
        Q->rpos[arow] = Q->tu; // Q��ǰ�еĵ�1��Ԫ��λ����1�����1��Ԫ��֮��
        if (arow < M->mu - 1) {
            tp = M->rpos[arow + 1];//��õ�һ�еķ���Ԫ������0��ʼ
        } else if (arow == M->mu - 1) {//˵�������һ���� ֱ�ӷ���ʣ�µķ���Ԫ�Ϳ���
            tp = M->tu;
        }
        for (p = M->rpos[arow]; p < tp; ++p) { // ��M��ǰ����ÿһ������Ԫ
            brow = M->data[p].j; // �ҵ���ӦԪ��N�е��к�(M��ǰԪ���к�)
            if (brow < N->mu - 1) {
                t = N->rpos[brow + 1];
            } else if(brow == N->mu-1) {
                t = N->tu; // �����1�����
            }
            for (q = N->rpos[brow]; q < t; ++q) {
                ccol = N->data[q].j; // �˻�Ԫ����Q���к�
                ctemp[ccol] += M->data[p].element * N->data[q].element;
            }
        } // ���Q�е�arow�еķ���Ԫ
        for(ccol=0;ccol<Q->nu;++ccol){ // ѹ���洢���з���Ԫ
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

void TransposeSMatrix(RLSMatrix* M,RLSMatrix* T) {// ��ϡ�����M��ת�þ���T
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
        num[col]=0;  // ���ֵ
    }
    for (t = 0; t < M->tu; ++t) {
        ++num[M->data[t].j];
    } // ��M��ÿһ�з���Ԫ���� ��������4 3
    T->rpos[0]=0;
    for (col = 1; col < M->nu; ++col) {
        T->rpos[col]=T->rpos[col-1]+num[col-1]; // 0 4
    } // ��M�е�col�е�һ������Ԫ��T.data�е���� ��������ת����������
    for (col = 0; col <M->nu; ++col) {
        num[col] = T->rpos[col];
    }
    for(p=0;p<M->tu;++p){
        col=M->data[p].j;
        q=num[col];
        T->data[q].j=M->data[p].i;
        T->data[q].i=M->data[p].j;
        T->data[q].element=M->data[p].element;
        ++num[col]; //ָʾ���е�����ÿ�������+1
    }
    free(num);
}
