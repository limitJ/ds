//
// Created by megumin on 2019/4/24.
//

#ifndef BINARYTREE_BINARYTREE_H
#define BINARYTREE_BINARYTREE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
typedef struct Node{
    void *data;
    struct Node* left;
    struct Node*  right;
}Node;
typedef struct BinaryTree{
    Node* root;
    int size;
    int (*compare)(const void* key1, const void* key2);
    void (*destroy)(void* data);
}BinaryTree;
void init_bitree(BinaryTree* binaryTree,void (*destroy)(void *data));
void destroy(BinaryTree* binaryTree);
bool bitree_ins_left(BinaryTree* binaryTree,Node* node, const void* data);//添加左孩子节点
bool bitree_ins_right(BinaryTree* binaryTree,Node* node, const void* data);
void bitree_rem_left(BinaryTree* binaryTree,Node* node);//删除指定节点左子树
void bitree_rem_right(BinaryTree* binaryTree,Node* node);
bool bitree_merge(BinaryTree* merge,BinaryTree* left_tree,BinaryTree* right_tree, const void* data);//归并2颗树
int depth(Node* root);
void prevorder(Node* root,void(*vist)(const void* data));
void inorder(Node* root,void(*vist)(const void* data));
void postorder(Node* root,void(*vist)(const void* data));
#endif //BINARYTREE_BINARYTREE_H
