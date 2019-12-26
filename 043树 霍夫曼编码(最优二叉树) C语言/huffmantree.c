//
// Created by zhubin on 2019/5/9.
//
//
#include "huffmantree.h"

int min(HuffmanTree* t,int i){ // ����i�������Ȩֵ��С�����ĸ������ţ�����select()����
    int j=0,flag = 0;
    unsigned int k=UINT_MAX; // ȡkΪ��С�ڿ��ܵ�ֵ(�޷����������ֵ)
    for(j=1;j<=i;j++) {
        if (t[j].weight < k && t[j].parent == 0) { // t[j]�����ĸ����
            k = t[j].weight;
            flag = j;
        }
    }
    t[flag].parent=1; // ��ѡ�еĸ�����˫�׸�1�������2�β��Ҹý��
    return flag;
}

void select(HuffmanTree* t,int i,int* s1,int* s2){ // ��i�������ѡ��2��Ȩֵ��С�����ĸ������ţ�s1Ϊ�������С���Ǹ�
    int j;
    *s1 = min(t,i);
    *s2 = min(t,i);
    if(*s1>*s2){
        j=*s1;
        *s1=*s2;
        *s2=j;
    }
}

void HuffmanCoding(HuffmanTree* HT, HuffmanCode HC, int* w, int len){
    int m,i,s1 = 0,s2 = 0,start;
    unsigned int c,f;
    m=2*len-1;//������Ĵ�СΪ Ҷ�ӽڵ�����*2-1
    for(i=1;i<=2*len-1;++i){  //HT��0�±������õ�
        if(i<=len){
            HT[i].weight=w[i-1];  //�ȳ�ʼ��ԭ�������Ȩֵ��Ҷ�ӽڵ�
        }
        HT[i].parent=0;
        HT[i].lchild=0;
        HT[i].rchild=0;
    }
    for(i=len+1;i<=m;++i){ // ��HT[1��i-1]��ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1��s2
        select(HT,i-1,&s1,&s2);
        HT[s1].parent=HT[s2].parent=i;
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
     //��Ҷ�ӵ���������ÿ���ַ��ĺշ�������
     //����n���ַ������ͷָ������([0]����)
    char* cd=(char*)malloc(len*sizeof(char)); // ���������Ĺ����ռ�
    cd[len-1]='\0'; // ���������
    for(i=1;i<=len;i++){ // ����ַ���շ�������
        start=len-1; // ���������λ��
        for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent){
            if(HT[f].lchild==c){
                cd[--start]='0';
            }
            else{
                cd[--start]='1';
            }
        }
         //Ϊ��i���ַ��������ռ�
        HC[i] = (char*)malloc((len - start) * sizeof(char));
         //��Ҷ�ӵ������������
        strcpy(HC[i],&cd[start]); // ��cd���Ʊ���(��)��HC
    }
    free(cd); // �ͷŹ����ռ�
}