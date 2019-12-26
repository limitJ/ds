#include "adjmap.h"
/*
 * 数据结构
 * 图 邻接表
 * 严蔚敏书上的全部13个关于图的基本操作
 * 由于严蔚敏的书上的操作要考虑有向图 有向网 无向图 无向网 非常的繁琐
 * 而且大部分不管无向有向 很多操作几乎大同小异 没有必要去重复实现
 * 因此为了程序的便捷只写一个有向网
 * 网上的代码自己太菜又看不懂 于是自己实现一个图
 * 和严蔚敏稍微有些区别的地方在于
 * 在ADT中 除了定义了firstarc外 还定义了tailarc用于方便链表的插入 size则记录了链表的长度
 *
 * 程序运行环境 编译通过 并运行成功
 * 编译器:MinGW gcc version 8.3
 * 操作系统：windows 10
 * IDE：CLion 2019.1
 * Cmake: 3.13
 *
 * 请勿在vc vs平台上运行本程序 不支持
 *
 * QQ 582521582
 * QQ群 322085520
 * 作者水平有限 BUG再所难免 欢迎阅读者指正 如有疑问和指正 请联系QQ或进QQ群讨论
 *
 * 程序测试用例如下
 * 请输入4个有向图中顶点的信息！
 * a b c d
 * 请输入5个有向图中弧的信息(各不超过8各字符) 弧尾 弧头 权值
 * a b 1
 * a d 1
 * b c 1
 * c a 1
 * c d 1
 * 顶点信息
 * [a] -> {1b -> 3d -> NULL}
 * 顶点信息
 * [b] -> {2c -> NULL}
 * 顶点信息
 * [c] -> {0a -> 3d -> NULL}
 * 顶点信息
 * [d] -> {NULL}
 * 索引为2的顶点 c
 * 将a顶点修改aa后查看结果 aa
 * 顶点c的第一个邻接点的位置和信息是 0 aa
 * -1
 * 顶点信息
 * [aa] -> {1b -> 2d -> NULL}
 * 顶点信息
 * [b] -> {NULL}
 * 顶点信息
 * [d] -> {NULL}
 * 删除顶点后的弧还剩 2个
 * 新的插入顶点e是否成功1
 * 请输入v w弧之间的权值weight
 * 1
 * 添加aa->e的一条弧是否成功:1
 * 顶点信息
 * [aa] -> {1b -> 2d -> 3e -> NULL}
 * 顶点信息
 * [b] -> {NULL}
 * 顶点信息
 * [d] -> {NULL}
 * 顶点信息
 * [e] -> {NULL}
 * 删除aa->d之间的弧是否成功:1
 * 顶点信息
 * [aa] -> {1b -> 3e -> NULL}
 * 顶点信息
 * [b] -> {NULL}
 * 顶点信息
 * [d] -> {NULL}
 * 顶点信息
 * [e] -> {NULL}
 * 请输入8个有向图中顶点的信息！
 * v1 v2 v3 v4 v5 v6 v7 v8
 * 请输入9个有向图中弧的信息(各不超过8各字符) 弧尾 弧头 权值
 * v1 v2 1
 * v1 v3 1
 * v2 v4 1
 * v2 v5 1
 * v4 v8 1
 * v5 v8 1
 * v3 v6 1
 * v3 v7 1
 * v6 v7 1
 * 顶点信息
 * [v1] -> {1v2 -> 2v3 -> NULL}
 * 顶点信息
 * [v2] -> {3v4 -> 4v5 -> NULL}
 * 顶点信息
 * [v3] -> {5v6 -> 6v7 -> NULL}
 * 顶点信息
 * [v4] -> {7v8 -> NULL}
 * 顶点信息
 * [v5] -> {7v8 -> NULL}
 * 顶点信息
 * [v6] -> {6v7 -> NULL}
 * 顶点信息
 * [v7] -> {NULL}
 * 顶点信息
 * [v8] -> {NULL}
 * DFS深度优先遍历图
 * v1 v2 v4 v8 v5 v3 v6 v7
 * BFS广度优先遍历图
 * v1 v2 v3 v4 v5 v6 v7 v8
 *
 * */
int main(void) {
    ALGraph *g = (ALGraph *) malloc(sizeof(ALGraph));
    createGraph(g, 4, 5);
    display(g);
    printf("索引为2的顶点 %s\n",getVex(g, 2));
    putVex(g, "a", "aa");
    printf("将a顶点修改aa后查看结果 %s\n", getVex(g, locateVex(g,"aa")));
    printf("顶点c的第一个邻接点的位置和信息是 %d %s\n", fristAdjVex(g, "c"), getVex(g, fristAdjVex(g, "c")));
    printf("b顶点中c的下一个节点信息序号是：%d\n", nextAdjVex(g, "b", "c"));
    deleteVex(g,"c");
    display(g);
    printf("删除顶点后的弧还剩 %d个\n", g->arc);
    printf("新的插入顶点e是否成功%d\n",insertVex(g, "e"));
    printf("添加aa->e的一条弧是否成功:%d\n",insertArc(g, "aa", "e"));
    display(g);
    printf("删除aa->d之间的弧是否成功:%d\n", deleteArc(g, "aa", "d"));
    display(g);
    ALGraph *graph = (ALGraph *) malloc(sizeof(ALGraph));
    createGraph(graph, 8, 9);
    display(graph);
    DFSTreverse(graph);
    BFSTreverse(graph);
    free(g);
    free(graph);
    return 0;
}