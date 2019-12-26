/*
 *
 * 数据结构
 * AVL 二叉平衡树
 * 平衡树分为种情况 一种是左旋 一种是右旋
 * 而左旋分为LL旋 LR旋 右旋分RR旋 RL旋
 * LR调整平衡因子分3种情况讨论 RL旋转也是分3种情况讨论
 * LL和RR是对称关系
 * LR和RL是对称关系
 * 运行环境 LLVM CLang v8.0
 * IDE CLion v2019-2
 * OS: ArchLinux DDE
 * C标准：c11
 * QQ 582521582
 * QQ群 322085520
 * */
#include <stdio.h>
#include "avltree.h"
#define len(arr) ((typeof(arr[0]))(sizeof(arr)/sizeof(typeof(arr[0]))))
int compare(const void* key1, const void* key2);

void destroy(void* data);

int main(void) {
    AvlTree *avlTree = (AvlTree *) malloc(sizeof(AvlTree));
    avlTree_init(avlTree,compare,destroy);
    int arr[] = {6, 2, 4, 1, 9, 8, 5, 3, 7, 0};
    for (int i = 0; i < len(arr); ++i) {
        avlTree_insert(avlTree, &arr[i]);
    }
    inoder(avlTree->root);
    avlTree_destroy(avlTree);
    free(avlTree);
    return 0;
}

int compare(const void* key1, const void* key2){
    return *(int*)key1 - *(int*)key2;
}

void destroy(void* data){
    data = NULL;
}