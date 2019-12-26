//
// Created by archlinux on 2019/7/27.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <stdbool.h>
#include "binarytree.h"
//定义平衡因子
#define AVL_LEFT_HEAVY 1
#define AVL_BALANCED 0
#define AVL_RIGHT_HEAVY -1
/*L R旋转其实不难 都是固定的步骤 只不过是步骤有点多而已 记起步骤来很麻烦*/
typedef struct AvlNode_{
    void* data;
    //hidden标示是否已经隐藏一个成员 惰性删除
    int hidden;
    int factor;
}AvlNode;

//定义avltree binarytree里面的泛型data数据存放 AvlNode 真实数据 又存放在AvlNode里的泛型data
typedef  BinaryTree AvlTree;

/*
 * 定义公共基本操作接口
 * */
void avlTree_init(AvlTree* avlTree,int(*compare)(const void* key1, const void* key2),void (destroy)(void* data));

void avlTree_destroy(AvlTree* avlTree);

int avlTree_insert(AvlTree* avlTree, const void* data);

bool avlTree_remove(AvlTree* avlTree, const void* data);

//查找某个节点 返回成data
bool avlTree_lookup(AvlTree* avlTree,void** data);

void inoder(Node* root);
#endif //AVLTREE_AVLTREE_H
