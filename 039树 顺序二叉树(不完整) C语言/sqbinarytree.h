//
// Created by megumin on 2019/4/22.
//

#ifndef TREE_SQBINARYTREE_H
#define TREE_SQBINARYTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define MAX_TREE_SIZE 1024 //最大节点数量
typedef struct Pos{
    int level;//节点尾
    int order;//本层序号
}Pos;
void InitBiTree(int* T);
void CreateBiTree(int* T);
bool isEmpty(int* T);
int Depth(int* T);
int Root(int* T);
int Value(int* T,Pos e);
bool Assign(int* T,Pos e,int value);
int Parent(int* T,int e);
int LeftChild(int* T,int e);
int RightChild(int* T,int e);
int LeftSibling(int* T,int e);
int RightSibling(int* T,int e);
#endif //TREE_SQBINARYTREE_H
