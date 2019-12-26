//
// Created by QQ 582521582 on 2019/2/24.
// QQȺ: 322085520
// ��Ԫ��ϡ�����Ļ�������
#include <stdio.h>
#include <stdlib.h>
#include "sparsematrix.h"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "missing_default_case"
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wlogical-op-parentheses"
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

void DestroySMatrix(TSMatrix* tsm){ // ����ϡ�����M
    tsm->mu=tsm->nu=tsm->tu=0;
}

void PrintSMatrix(TSMatrix* TSM){ // ���ϡ�����M
    int i;
    printf("%d��%d��%d������Ԫ�ء�\n",TSM->mu,TSM->nu,TSM->tu);
    printf("��  ��  Ԫ��ֵ\n");
    for(i=0;i<TSM->tu;i++)
        printf("%d%4d%6d\n",TSM->data[i].i,TSM->data[i].j,TSM->data[i].element);
}
void PrintSMatrix1(TSMatrix* M){ // ��������ʽ���M
    int i,j,k=0;
    Triple *p=M->data;
    for(i=0;i<M->mu;i++){
        for(j=0;j<M->nu;j++)
            if(k<M->tu&&p->i==i&&p->j==j){ // pָ�����Ԫ����p��ָԪ��Ϊ��ǰ����Ԫ��
                printf("%3d",p->element); // ���p��ָԪ�ص�ֵ
                p++; // pָ����һ��Ԫ��
                k++; // ������+1
            }
            else { // p��ָԪ�ز��ǵ�ǰ����Ԫ��
                printf("%3d", 0); // ���0
            }
        printf("\n");
    }
}

void CopySMatrix(TSMatrix* M,TSMatrix* T){ // ��ϡ�����M���Ƶõ�T
    *T = *M;
}

int comp(int c1,int c2){ // AddSMatrix����Ҫ��
    if(c1<c2) {
        return -1;
    }
    if(c1==c2) {
        return 0;
    }
    return 1;
}

bool AddSMatrix(TSMatrix* M,TSMatrix* N,TSMatrix* Q){ // ��ϡ�����ĺ�Q=M+N
    int m=0,n=0,q=0;
    if(M->mu!=N->mu||M->nu!=N->nu) { // M��N��ϡ������л�������ͬ
        puts("�������в�һ��,�޷����������������");
        return false;
    }
    Q->mu=M->mu;
    Q->nu=M->nu;
    while(m<M->tu&&n<N->tu){ // ����M��N��Ԫ�ض�û������
        switch(comp(M->data[m].i,N->data[n].i)){
            case -1:
                Q->data[q].i=M->data[m].i; // ������M�ĵ�ǰԪ��ֵ��������Q
                Q->data[q].j = M->data[m].j;
                Q->data[q].element = M->data[m].element;
                q++;
                m++;
                break;
            case  0:
                switch(comp(M->data[m].j,N->data[n].j)){ // M��N����ǰԪ�ص������,�����Ƚ���
                    case -1:
                        Q->data[q].i=M->data[m].i; // ������M�ĵ�ǰԪ��ֵ��������Q
                        Q->data[q].j = M->data[m].j;
                        Q->data[q].element = M->data[m].element;
                        q++;
                        m++;
                        break;
                    case  0:
                        Q->data[q].i = M->data[m].i;
                        Q->data[q].j = M->data[m].j;
                        Q->data[q].element =M->data[m].element+N->data[n++].element; // ����M��N�ĵ�ǰԪ��ֵ��Ͳ���������Q
                        m++;
                        q++;
                        break;
                    case  1:
                        Q->data[q].i=N->data[n].i; // ������M�ĵ�ǰԪ��ֵ��������Q
                        Q->data[q].j = N->data[n].j;
                        Q->data[q].element = N->data[n].element;
                        q++;
                        n++;
                        break;

                }
                break;
            case  1:
                Q->data[q].i=N->data[n].i; // ������M�ĵ�ǰԪ��ֵ��������Q
                Q->data[q].j = N->data[n].j;
                Q->data[q].element = N->data[n].element;
                q++;
                n++;
                break;
            }
    }
    while(m<M->tu) { // ����N��Ԫ��ȫ���������
        Q->data[q].i = M->data[m].i;
        Q->data[q].j = M->data[m].j;
        Q->data[q].element =M->data[m].element+N->data[n++].element; // ����M��N�ĵ�ǰԪ��ֵ��Ͳ���������Q
        m++;
        q++;
    }
    while(n<N->tu) { // ����M��Ԫ��ȫ���������
        Q->data[q].i=N->data[n].i; // ������M�ĵ�ǰԪ��ֵ��������Q
        Q->data[q].j = N->data[n].j;
        Q->data[q].element = N->data[n].element;
        q++;
        n++;
    }
    Q->tu=q; // ����Q�ķ���Ԫ�ظ���
    if(q>MAXSIZE) { // ����Ԫ�ظ���̫��
        return false;
    }
    return true;
}

bool SubtSMatrix(TSMatrix* M,TSMatrix* N,TSMatrix* Q){ // ��ϡ�����Ĳ�Q=M-N
    int i;
    for (i = 1; i <= N->tu; i++) {
        N->data[i].element*=-1;
    }
    AddSMatrix(M,N,Q);
    return true;
}

void TransposeSMatrix(TSMatrix* M,TSMatrix* T){ // ��ϡ�����M��ת�þ���T��
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

bool MultSMatrix(TSMatrix* M,TSMatrix* N,TSMatrix* Q){ // ��ϡ�����ĳ˻�Q=M��N
    int i,j;
    int *Nc,*Tc;
    TSMatrix* T = (TSMatrix*)malloc(sizeof(TSMatrix)); // ��ʱ����
    printf("%d %d\n", M->nu, N->mu);
    if (M->nu != N->mu) {
        return false;
    }
    T->nu=M->mu; // ��ʱ����T��Q��ת�Ⱦ���
    T->mu=N->nu;
    T->tu=0;
    Nc=(int*)malloc((N->mu)*sizeof(int)); // NcΪ����Nһ�е���ʱ����(��ѹ��,����)
    Tc=(int*)malloc((M->nu)*sizeof(int)); // TcΪ����Tһ�е���ʱ����(��ѹ��,����)
    if(!Nc||!Tc) { // ������ʱ���鲻�ɹ�
        exit(-1);
    }
    for(i=0;i<N->nu;i++){ // ����N��ÿһ��
        for(j=0;j<N->mu;j++){
            Nc[j]=0; // ����Nc�ĳ�ֵΪ0
        }
        for(j=0;j<M->mu;j++) {
            Tc[j] = 0; // ��ʱ����Tc�ĳ�ֵΪ0

        }
        for(j=0;j<N->tu;j++) { // ����N��ÿһ������Ԫ��
            if (N->data[j].j == i) {// ���ڵ�i��
                Nc[N->data[j].i] = N->data[j].element; // �����������н���Ԫ��ֵ������Ӧ��Nc
            }
        }
        for(j=0;j<M->tu;j++) { // ����M��ÿһ��ֵ
            Tc[M->data[j].i] += M->data[j].element * Nc[M->data[j].j]; // Tc�д�N�ĵ�i����M��˵Ľ��
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
    } // ����Ԫ�ظ���̫��
    TransposeSMatrix(T,Q); // ��T��ת�ȸ���Q
    DestroySMatrix(T);
    free(Nc);
    free(Tc);
    return true;
}

#pragma clang diagnostic pop