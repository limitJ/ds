//
// Created by archlinux on 2019/7/27.
//
#include "avltree.h"
#include <stdlib.h>
#include <string.h>
//这里说一下static函数的作用 在函数前修饰static 代表只能在本文件中使用这个函数 并且可以轻松判断调用了几次这个函数
static void destroy_right(AvlTree* avlTree,Node* node);

/*
 * L旋
 * 分2种情况 LL旋转和LR旋转
 * 传入被破坏平衡的节点
 * */
static void L(Node** node){
    //左孩子 左孙子
    Node* left,*grandchild;
    left = (*node)->left;//被破坏平衡节点的左节点 先记录下来 防止下面旋转操作时候丢失指针
    if(((AvlNode*)left->data)->factor == AVL_LEFT_HEAVY){
        /*
         * LL旋转 当被破坏的left节点的平衡因子是1 左子树深度比右子树大1
         * 具体如下所示  参考书籍 在<<算法精解c语言描述>>一书第170页的LL旋转执行步骤图
         * 旋转前 E为插入的节点
         *          A(2)
         *    B(1)      F(0)
         * C(1)  D(0)
         *E(0)
         * 旋转后应该是
         *       B(0)
         *  C(1)      A(0)
         *E(0)     D(0)  F(0)
         *旋转步骤
         *1：将A的左指针指向B的右孩子(D在A的左边 说明D肯定是比A小的)
         *2：将B也就是left的右指针指向A (原本B比A小 旋转后B要作为根节点 根据插入规则 A必然大于B 所以A应插入右边 )
         *3: 将原先指向A的上一层指针 重新指向B
         * */
        (*node)->left = left->right; //对应步骤1
        left->right = *node; //对应步骤2
        //平衡因子的变化在4个操作里面是固定的 在上面也有实例 LL旋转变化的就这2个
        (((AvlNode*)(*node)->data))->factor = AVL_BALANCED;
        (((AvlNode*)(*node)->left->data))->factor = AVL_BALANCED;
        *node = left;//对应步骤3
    }else{
        /* LR旋转
         * E 为插入节点
         * 被破坏平衡节点的左子树的平衡因子是-1
         * 插入后被破坏树的状态
         *              A(2)
         *      B(-1)       F(0)
         *  C(0)    D(1)
         *       E(0)   插在grandchild左边   注意这里插入左右不同 将影响后面平衡因子的调整方式 后面有3种情况讨论
         *
         * 平衡后的状态 这只是其中一种状态 一共3种状态下面有讨论
         *
         *            D(0)
         *      B(0)       A(-1)
         *   C(0)  E(0) NULL    F(0)
         *           E为插入节点
         * LR旋转步骤
         * 1:将B的右指针指向D的左右孩子X 前提是先要保存记录下D的节点 防止指针丢失
         *   X在B的右边的 说明无论如何X都比B大 因此可以保存在B的右孩子节点
         * 2:将D的left节点指向B D在B的右子树上 说明D肯定大于B D将作为根节点使用
         * 3：A的左孩子指向D的右孩子 本例中讨论的插在D的左孩子 所以相当于NULL 稍后讨论3中情况
         * 4：将D的右孩子指向A 原本旋转前D在A的左孩子 所以D必然小于A 因此当D作为根节点 A应当插在D的右边
         * 5：将原本指向A的的左指针指向D 并更新A left grandchild的节点平衡因子
         * */
        grandchild = left->right;//先保存下 防止后续旋转操作指针丢失
        left->right = grandchild->left;//步骤1
        grandchild->left = left;//步骤2
        (*node)->left = grandchild->right;//步骤3
        grandchild->right = *node;//步骤4
        /*
         * 接下来是平衡因子调整的讨论 一共有3种情况讨论
         * 3种情况地方讨论取决与grandchild的平衡因子的情况
         * 这里了解下 每一种情况 被作为根的D节点 也就是grandchild的平衡因子一定为0
         * 根据grandchild的平衡因子来讨论
         *
         * 第一种情况：grandchild的平衡因子=1
         * E是插入grandchild的左子树的时候
         * 也就是本例子中使用的方式 平衡后可以只管看出 A left grandchil应该调整为 -1 0 0
         *
         * 第二种情况：grandchild的平衡因子=0
         * 也就是说E就是插入的本身 也就是grandchild
         * 插入前失衡状态
         *            A(2)
         *      B(-1)       注意这里也没有F 因为LR旋转 A的平衡因子必须是2
         *            D(0) grandchild本身   注意这里没有C节点了 因为要保证LR旋转的话 B平衡因子必须为-1
         * 平衡后的状态
         *           D(0)
         *      B(0)    A(0)
         * 可以看出本例中的平衡状态 A left grandchild(D) 平衡后的平衡因子为 0 0 0
         *
         * 第三种情况：grandchild的平衡因子=-1
         * 也就是插入节点E 插在了grandchild的右边
         * 插入前失衡状态
         *             A(2)
         *      B（-1)       F(0)
         *  C(0)    D(-1)
         *              E(0)    插在grandchild右边
         * 平衡后的状态
         *              D(0)
         *       B(1)          A(0)
         *   C(0)   NULL   E(0)    F(0)
         *  可以看到这种情况下的A left grandchild(D)的平衡状态为 0 1 0
         * */
        switch (((AvlNode*)grandchild->data)->factor){
            case AVL_LEFT_HEAVY:
                (((AvlNode*)(*node)->data))->factor = AVL_RIGHT_HEAVY;
                (((AvlNode*)left->data))->factor = AVL_BALANCED;
                break;
            case AVL_BALANCED:
                (((AvlNode*)(*node)->data))->factor = AVL_BALANCED;
                (((AvlNode*)left->data))->factor = AVL_BALANCED;
                break;
            case AVL_RIGHT_HEAVY:
                (((AvlNode*)(*node)->data))->factor = AVL_BALANCED;
                (((AvlNode*)left->data))->factor = AVL_LEFT_HEAVY;
                break;
        }
        (((AvlNode*)grandchild->data))->factor = AVL_BALANCED;
        *node = grandchild;//步骤5
    }
}

/*
 * R旋
 * 也分2种情况 RR旋转和RL旋转
 * 道理和L旋是一样的同理 就不多写注释了
 * */
static void R(Node** node){
    Node* right,*grandchild;
    right = (*node)->right;
    if(((AvlNode*)(right->data))->factor == AVL_RIGHT_HEAVY){
        //RR旋 插在的node的右子树的右子树
        (*node)->right = right->left;
        right->left = *node;
        (((AvlNode*)(*node)->data))->factor = AVL_BALANCED;
        (((AvlNode*)(*node)->right->data))->factor = AVL_BALANCED;
        *node = right;
    }else{
        grandchild = right->left;
        right->left = grandchild->right;
        grandchild->right = right;
        (*node)->right = grandchild->left;
        grandchild->left = *node;
        switch (((AvlNode*)grandchild->data)->factor){
            case AVL_LEFT_HEAVY:
                (((AvlNode*)(*node)->data))->factor = AVL_BALANCED;
                (((AvlNode*)right->data))->factor = AVL_RIGHT_HEAVY;
                break;
            case AVL_BALANCED:
                (((AvlNode*)(*node)->data))->factor = AVL_BALANCED;
                (((AvlNode*)right->data))->factor = AVL_BALANCED;
                break;
            case AVL_RIGHT_HEAVY:
                (((AvlNode*)(*node)->data))->factor = AVL_LEFT_HEAVY;
                (((AvlNode*)right->data))->factor = AVL_BALANCED;
                break;
        }
        (((AvlNode*)grandchild->data))->factor = AVL_BALANCED;
        *node = grandchild;
    }
}

//递归删除某一节点的左子树
static void destroy_left(AvlTree* avlTree,Node* node){
    Node** postion;
    if (avlTree->size == 0){
        return;
    }
    if (node == NULL){
        postion = &avlTree->root;
    }else{
        postion = &node->left;
    }
    if (*postion != NULL){
        destroy_left(avlTree,*postion);
        destroy_right(avlTree, *postion);
        if(avlTree->destroy!=NULL){
            avlTree->destroy(((AvlNode*)(*postion)->data)->data);
        }
        free((*postion)->data);
        free(*postion);
        *postion = NULL;
        avlTree->size--;
    }
}

//递归删除某一节点的右子树
static void destroy_right(AvlTree* avlTree,Node* node){
    Node** postion;
    if (avlTree->size == 0){
        return;
    }
    if (node == NULL){
        postion = &avlTree->root;
    }else{
        postion = &node->right;
    }
    if (*postion != NULL){
        destroy_left(avlTree,*postion);
        destroy_right(avlTree, *postion);
        if(avlTree->destroy!=NULL){
            avlTree->destroy(((AvlNode*)(*postion)->data)->data);
        }
        free((*postion)->data);
        free(*postion);
        *postion = NULL;
        avlTree->size--;
    }
}

/*
 * 平衡树递归插入
 * */
static int insert(AvlTree* avlTree, Node** node, const void* data,int *balanced){
    AvlNode* avl_data;
    int cmpval = 0;//插入比较插在左边还是右边
    int retval = 0;//得出递归调用的层数
    /*
     *开始插入了
     * */
    if(*node == NULL){
        //当还是一颗空树的时候 初始化根节点数据
        avl_data = (AvlNode*)malloc(sizeof(AvlNode));
        if (avl_data == NULL){
            return false;
        }
        avl_data->factor = AVL_BALANCED;
        avl_data->hidden = 0;
        avl_data->data = (void*)data;
        return bitree_ins_left(avlTree,*node,avl_data);//实际上当node是null的时候 无论左右插入 最后都是作为根节点
    }else{
        //看插入的节点和根节点比较 比root小 插入左边 比root大插入右边
        cmpval = avlTree->compare(data,((AvlNode*)(*node)->data)->data);
        //当插入数据比root小 应该插入左边
        if(cmpval<0){
            if ((*node)->left == NULL){
                //如果左边是空的 就直接插入左节点
                avl_data = (AvlNode*)malloc(sizeof(AvlNode));
                if (avl_data == NULL){
                    return false;
                }
                avl_data->factor = AVL_BALANCED;
                avl_data->hidden = 0;
                avl_data->data = (void*)data;
                if(bitree_ins_left(avlTree,*node,avl_data)!=true){
                    return false;
                }
                *balanced = 0;
            }else{
                //递归插入
                if((retval = insert(avlTree,&(*node)->left,data,balanced))!=0){
                    return retval;
                }
            }
            //在递归过程中 我们要对树的平衡因子 进行调整
            //这里难在有个代码递归执行有个回溯的过程 比如插入 6 2 1  插入 6 2后 6(1) 2(1) 1(0)
            //括号内是平衡因子 插入完1后 递归要回溯 这时候node是6 6再次传入switch的时候 平衡因子是1 就要执行L左旋
            //所以左旋传入的是node 6
            if(!(*balanced)){
                 switch (((AvlNode*)(*node)->data)->factor){
                    case AVL_LEFT_HEAVY:
                        L(node);
                        *balanced = 1;
                        break;
                    case AVL_BALANCED:
                        (((AvlNode*)(*node)->data))->factor = AVL_LEFT_HEAVY;
                        break;
                    case AVL_RIGHT_HEAVY:
                        (((AvlNode*)(*node)->data))->factor = AVL_BALANCED;
                        *balanced = 1;
                        break;
                }
            }
        }else if(cmpval>0){//cmpval>0 也就是待插入数据比root大
            if ((*node)->right == NULL){
                //如果左边是空的 就直接插入左节点
                avl_data = (AvlNode*)malloc(sizeof(AvlNode));
                if (avl_data == NULL){
                    return false;
                }
                avl_data->factor = AVL_BALANCED;
                avl_data->hidden = 0;
                avl_data->data = (void*)data;
                if(bitree_ins_right(avlTree,*node,avl_data)!=true){
                    return false;
                }
                *balanced = 0;
            }else{
                //递归插入
                if((retval = insert(avlTree,&(*node)->right,data,balanced))!=0){
                    return retval;
                }
            }
            //在递归过程中 我们要对树的平衡因子 进行调整
            //这里代码是比较难懂的 主要这里有个递归回溯的过程
            if(!(*balanced)){
                switch (((AvlNode*)(*node)->data)->factor){
                    case AVL_LEFT_HEAVY:
                        (((AvlNode*)(*node)->data))->factor = AVL_BALANCED;
                        *balanced = 1;
                        break;
                    case AVL_BALANCED:
                        (((AvlNode*)(*node)->data))->factor = AVL_RIGHT_HEAVY;
                        break;
                    case AVL_RIGHT_HEAVY:
                        R(node);
                        *balanced = 1;
                        break;
                }
            }

        }else{//cmpval == 0 插入数值是一样的时候
            if (!((AvlNode*)(*node)->data)->hidden){
                return 1;
            }else{
                if(avlTree->destroy!=NULL){
                    avlTree->destroy(((AvlNode*)(*node)->data));
                }
                ((AvlNode*)(*node)->data)->data = (void*)data;
                ((AvlNode*)(*node)->data)->hidden = 0;
                *balanced = 1;
            }
        }
    }
    return 0;
}

static int hideen(AvlTree* avlTree,Node* node, const void* data){
    int cmpval = 0;
    int retval = 0;
    if(node == NULL){
        return -1;
    }
    cmpval = avlTree->compare(data,((AvlNode*)(node->data))->data);
    if (cmpval < 0) {
        retval = hideen(avlTree,node->left,data);
    } else if (cmpval > 0) {
        retval = hideen(avlTree, node->right, data);
    }else{
        (((AvlNode*)node->data))->hidden = 1;
        retval = 0;
    }
    return retval;
}

static int lookup(AvlTree* avlTree,Node* node,void** data){
    int cmpval = 0;
    int retval = 0;
    if (node == NULL) {
        return -1;
    }
    cmpval = avlTree->compare(data,((AvlNode*)(node->data))->data);
    if (cmpval < 0) {
        retval = lookup(avlTree,node->left,data);
    } else if (cmpval > 0) {
        retval = lookup(avlTree,node->left,data);
    }else{
        if(!(((AvlNode*)node->data))->hidden){
            *data = ((AvlNode*)node->data)->data;
            retval = 0;
        }else{
            return -1;
        }
    }
    return retval;
}

int avlTree_insert(AvlTree* avlTree, const void* data){
    int balabced = 0;
    return insert(avlTree,&avlTree->root,data,&balabced);
}

void avlTree_init(AvlTree* avlTree,int(*compare)(const void* key1, const void* key2),void (*destroy)(void* data)){
    init_bitree(avlTree, destroy);
    avlTree->compare = compare;
}

void avlTree_destroy(AvlTree* avlTree){
    destroy_left(avlTree, NULL);
    memset(avlTree,0, sizeof(AvlTree));
}

bool avlTree_remove(AvlTree* avlTree, const void* data){
    return hideen(avlTree, avlTree->root, data);
}

bool avlTree_lookup(AvlTree* avlTree,void** data){
    return lookup(avlTree, avlTree->root, data);
}
void inoder(Node* root){
    if (root != NULL) {
        inoder(root->left);
        printf("%d ",*(int*)((AvlNode*)(root->data))->data);
        inoder(root->right);
    }
}