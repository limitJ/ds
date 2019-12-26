//
// Created by megumin on 2019/4/24.
//
#include "binarytree.h"
void init_bitree(BinaryTree* binaryTree,void (*destroy)(void *data)){
    binaryTree->root = NULL;
    binaryTree->size = 0;
    binaryTree->destroy = destroy;
}
void destroy(BinaryTree* binaryTree){
    bitree_rem_left(binaryTree, NULL);
    memset(binaryTree, 0, sizeof(BinaryTree));
}
bool bitree_ins_left(BinaryTree* binaryTree,Node* node, const void* data){
    Node* new_node;
    Node** postion;
    if (node == NULL) {//当是一个空树的时候 先给root节点赋值
        if (binaryTree->size > 0) {
            return false;
        }
        postion = &binaryTree->root;
    }
    else
    {
        if (node->left != NULL){//插入左节点 则左节点必须有空位 否则报错
            return false;
        }
        postion = &node->left;//不是空树 就在插入左节点
    }
    new_node = (Node *) malloc(sizeof(Node));//分配节点
    if (new_node == NULL) {
        return false;
    }
    new_node->data = (void*)data;
    new_node->left = NULL;//初始化新节点左右孩子
    new_node->right = NULL;
    *postion = new_node;
    binaryTree->size++;//长度+1
    return true;
}
bool bitree_ins_right(BinaryTree* binaryTree,Node* node, const void* data){
    //
    Node* new_node;
    Node** postion;
    if (node == NULL) {
        if (binaryTree->size > 0) {
            return false;
        }
        postion = &binaryTree->root;
    }
    else
    {
        if (node->right != NULL) {
            return false;
        }
        postion = &node->right;
    }
    new_node = (Node *) malloc(sizeof(Node));
    if (new_node == NULL) {
        return false;
    }
    new_node->data = (void*)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *postion = new_node;
    binaryTree->size++;
    return true;
}
void bitree_rem_left(BinaryTree* binaryTree,Node* node){
    Node** position;
    if (binaryTree->size == 0) {//空树不需要删除
        return;
    }
    if (node == NULL) {//当node为NULL意味着从根节点开始删除整颗树
        position = &binaryTree->root;
    }
    else{
        position = &node->left;//删除指定节点的左子树
    }
    if (*position != NULL) {//遍历到叶子节点的时候开始递归返回
        bitree_rem_left(binaryTree, *position);
        bitree_rem_right(binaryTree, *position);
        if (binaryTree->destroy != NULL) {
            binaryTree->destroy((*position)->data);
        }
        free(*position);
        *position = NULL;
        binaryTree->size--;
    }
}
void bitree_rem_right(BinaryTree* binaryTree,Node* node){
    Node** position;
    if (binaryTree->size == 0) {
        return;
    }
    if (node == NULL) {
        position = &binaryTree->root;
    }
    else{
        position = &node->right;
    }
    if (*position != NULL) {
        bitree_rem_left(binaryTree, *position);
        bitree_rem_right(binaryTree, *position);
        if (binaryTree->destroy != NULL) {
            binaryTree->destroy((*position)->data);
        }
        free(*position);
        *position = NULL;
        binaryTree->size--;
    }
}
bool bitree_merge(BinaryTree* merge,BinaryTree* left_tree,BinaryTree* right_tree, const void* data){
    init_bitree(merge, left_tree->destroy);
    if (bitree_ins_left(merge, NULL, data)==false) {//先给merge根节点赋值
        destroy(merge);
        return false;
    }
    merge->root->left = left_tree->root;//让2棵树的根节点分别归并到merge上
    merge->root->right = right_tree->root;
    merge->size = merge->size + left_tree->size + right_tree->size;
    left_tree->size = 0;//不要让原始的节点访问新的节点
    left_tree->root = NULL;
    right_tree->size = 0;
    right_tree->root = NULL;
    return true;
}
int depth(Node* root){
    if (root != NULL) {
        int d1 = depth(root->left);
        int d2 = depth(root->right);
        int max = (d1 > d2 ? d1 : d2);
        return max+1;
    }
}