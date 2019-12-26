//
// Created by megumin on 2019/5/9.
//

#ifndef HUFFMANTREE_HUFFMANTREE_H
#define HUFFMANTREE_HUFFMANTREE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define len(arr) (int)(sizeof(arr)/sizeof(arr[0]))
typedef struct HuffmanTree{ //严蔚敏书上的赫夫曼树是用数组模拟的
    unsigned int weight;
    unsigned int parent;
    unsigned int lchild;
    unsigned int rchild;
}HuffmanTree; // 动态分配数组存储赫夫曼树
typedef char **HuffmanCode; // 动态分配数组存储赫夫曼编码表
void HuffmanCoding(HuffmanTree* HT, HuffmanCode HC, int *w, int n);
void select(HuffmanTree* t,int i,int* s1,int* s2);
#endif //HUFFMANTREE_HUFFMANTREE_H
