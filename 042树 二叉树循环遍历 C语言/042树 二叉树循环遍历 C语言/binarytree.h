#ifndef PROJECT1_BINARYTREE_H
#define PROJECT1_BINARYTREE_H
/*
 *  数据结构 二叉树树的循环遍历
 *  运行环境 Arch Linux (Manjaro Linux 18.04)KDE
 *  编译器 LLVM Clang 8.0
 *  请不要尝试在其他编译器中运行
 *  qq 582521582
 *  QQ群 322085520
 * */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#define len(arr) (int)sizeof(arr)/(int)sizeof(arr[0])
typedef struct Node{
	int data;
	struct Node* left;
	struct Node* right;
}Node;
typedef struct BinaryTree{
	Node* root;
	int size;
}BinaryTree;
void init_tree(BinaryTree* bitree);
void create_tree(BinaryTree* bitree,int data);
void inOrder(Node* root);
void prevOrder(Node* root);
void postOrder(Node* root);
void inor(Node* root);
void prevor(Node* root);
void postor(Node* root);
void clearBiTree(Node* root);
#endif