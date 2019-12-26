//
// Created by zhubin on 2019/5/9.
//
//
#include "huffmantree.h"

int min(HuffmanTree* t,int i){ // 返回i个结点中权值最小的树的根结点序号，函数select()调用
    int j=0,flag = 0;
    unsigned int k=UINT_MAX; // 取k为不小于可能的值(无符号整型最大值)
    for(j=1;j<=i;j++) {
        if (t[j].weight < k && t[j].parent == 0) { // t[j]是树的根结点
            k = t[j].weight;
            flag = j;
        }
    }
    t[flag].parent=1; // 给选中的根结点的双亲赋1，避免第2次查找该结点
    return flag;
}

void select(HuffmanTree* t,int i,int* s1,int* s2){ // 在i个结点中选择2个权值最小的树的根结点序号，s1为其中序号小的那个
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
    m=2*len-1;//整个表的大小为 叶子节点数量*2-1
    for(i=1;i<=2*len-1;++i){  //HT的0下标是弃用的
        if(i<=len){
            HT[i].weight=w[i-1];  //先初始化原本那你带权值的叶子节点
        }
        HT[i].parent=0;
        HT[i].lchild=0;
        HT[i].rchild=0;
    }
    for(i=len+1;i<=m;++i){ // 在HT[1～i-1]中选择parent为0且weight最小的两个结点，其序号分别为s1和s2
        select(HT,i-1,&s1,&s2);
        HT[s1].parent=HT[s2].parent=i;
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
     //从叶子到根逆向求每个字符的赫夫曼编码
     //分配n个字符编码的头指针向量([0]不用)
    char* cd=(char*)malloc(len*sizeof(char)); // 分配求编码的工作空间
    cd[len-1]='\0'; // 编码结束符
    for(i=1;i<=len;i++){ // 逐个字符求赫夫曼编码
        start=len-1; // 编码结束符位置
        for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent){
            if(HT[f].lchild==c){
                cd[--start]='0';
            }
            else{
                cd[--start]='1';
            }
        }
         //为第i个字符编码分配空间
        HC[i] = (char*)malloc((len - start) * sizeof(char));
         //从叶子到根逆向求编码
        strcpy(HC[i],&cd[start]); // 从cd复制编码(串)到HC
    }
    free(cd); // 释放工作空间
}