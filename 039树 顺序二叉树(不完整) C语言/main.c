/*
 *
 * 树 n(n>=0)个节点的有限集
 * 一颗非空树中
 * 仅有一个根节点root
 * 对于顺序存储结构 insertChild delete不写了 不会
 * 遍历麻烦 也不写了
 *
 * */
#include "sqbinarytree.h"
int main(void)
{
    int sqbt[MAX_TREE_SIZE] = {
            1,2,3,4,5,6,0,7,8,9,0,10,0,0,0,0
    };
    //二叉树对应存储形式如下
    /*0代表空间 公式(i+1)/2 - 1等于该节点的父节点序号 i为当前位置节点 空节点的是不许有孩子节点的
     * 同样的 孩子节点的父亲节点是不可以为0空节点的 这里在create会判断比如这里把6改成0 就会报错
     *            1
     *      2           3
     *   4     5     6     0
     *  7 8   9 0  10 0   0 0
     *
     * */
    InitBiTree(sqbt);
    CreateBiTree(sqbt);
    printf("是够为空：%d\n", isEmpty(sqbt));
    printf("深度 %d\n", Depth(sqbt));
    printf("树根: %d\n", Root(sqbt));
}