//
// Created by QQ 582521582 on 2019/2/24.
// QQȺ: 322085520
// ��Ԫ��ϡ����� �û��㷨
#include <stdio.h>
#include <stdlib.h>
#include "sparsematrix.h"
bool CreateSMatrix(TSMatrix* TSM,int matrix[][7],int col,int row){ // ����ϡ�����TSM
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

void PrintSMatrix(TSMatrix* TSM){ // ���ϡ�����M
    int i;
    printf("%d��%d��%d������Ԫ�ء�\n",TSM->mu,TSM->nu,TSM->tu);
    printf("��  ��  Ԫ��ֵ\n");
    for(i=0;i<TSM->tu;i++)
        printf("%d%4d%6d\n",TSM->data[i].i,TSM->data[i].j,TSM->data[i].element);
}
void FastTransposeSMatrix(TSMatrix* M,TSMatrix* T){ // ������ϡ�����M��ת�þ���T��
    int q=0,col = 0;
    int* num=(int *)malloc(M->nu*sizeof(int)); // ��Mÿ��(Tÿ��)����Ԫ�ظ���)
    int* cpot=(int *)malloc(M->nu*sizeof(int)); // ��Tÿ�е���1������Ԫ�صĴ洢λ��)
    T->mu=M->nu; // ��T���С����������Ԫ�ظ�����ֵ
    T->nu=M->mu;
    T->tu=M->tu;
    if(T->tu!=0) { // �Ƿ������{
        for (col = 0; col < M->nu; ++col) {
            num[col] = 0; // ��������ֵ��Ϊ0
            cpot[col] = 0;
        }
    }
    for(int t=0;t<M->tu;++t) { // ��M��ÿһ�к�����Ԫ�ظ���
        ++num[M->data[t].j];
    }
    for(col=1;col<M->nu;++col) {
        cpot[col] = cpot[col-1] + num[col-1]; // ��T�ĵ�col�еĵ�1������Ԫ��T.data�е����
        //��һ������Ԫ��λ����numȷ�� ����num[0]��2��Ԫ��!��ô�����j��1 ��˵������0���е�Ԫ�� λ�þ��Ǳ����T���ڵ�λ��
    }
    for(int p=0;p<M->tu;++p){ // ��M�ĵ�0��Ԫ�ؿ�ʼ
        col=M->data[p].j; // �����M�е�����
        q=cpot[col]; // qָʾM��ǰ��Ԫ����T�е����
        T->data[q].i=M->data[p].j;
        T->data[q].j=M->data[p].i;
        T->data[q].element=M->data[p].element;
        ++cpot[col]; // T��col�е���1������Ԫ��T.data�е����
    }
    free(num);
    free(cpot);
}