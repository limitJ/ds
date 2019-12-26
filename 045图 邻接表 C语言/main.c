/*
 * 图 邻接表
 * 严蔚敏的代码是在太深涩难懂了 这里打算重写图的代码实现
 * 为了精简代码量 避免重复代码 这里只实现 有向网
 * 其他的有向图 无向图 无向网几乎大同小异 改变的地方很少 因此这里不去实现其他3种
 * QQ 582521582
 * QQ群 322085520
 * 本程序完全本人实现 但作者水平有限 错误在所难免 欢迎阅者指正
 * DFS BFS的代码打算单独一个程序里写 如果需要代码 请加QQ群
 *
 * 本程序运行环境 MinGW gcc8.3
 * 编译器 CLion2019.1
 * c标准 c11
 * 请勿在vs vc平台下运行 因为不支持
 *
 *  程序测试用例如下
 *  请输入4个有向图中顶点的信息！
 *  a b c d
 *  请输入5个有向图中弧的信息(各不超过8各字符) 弧尾 弧头 权值
 *  a b 1
 *  a d 1
 *  b c 1
 *  c a 1
 *  c d 1
 *  顶点信息
 *  [a] -> {1b -> 3d -> NULL}
 *  顶点信息
 *  [b] -> {2c -> NULL}
 *  顶点信息
 *  [c] -> {0a -> 3d -> NULL}
 *  顶点信息
 *  [d] -> {NULL}
 *  索引为2的顶点 c
 *  将a顶点修改aa后查看结果 aa
 *  顶点c的第一个邻接点的位置和信息是 0 aa
 *  -1
 *  顶点信息
 *  [aa] -> {1b -> 2d -> NULL}
 *  顶点信息
 *  [b] -> {NULL}
 *  顶点信息
 *  [d] -> {NULL}
 *  删除顶点后的弧还剩 2个
 *  新的插入顶点e是否成功1
 *  请输入v w弧之间的权值weight
 *  1
 *  添加aa->e的一条弧是否成功:1
 *  顶点信息
 *  [aa] -> {1b -> 2d -> 3e -> NULL}
 *  顶点信息
 *  [b] -> {NULL}
 *  顶点信息
 *  [d] -> {NULL}
 *  顶点信息
 *  [e] -> {NULL}
 *  删除aa->d之间的弧是否成功:1
 *  顶点信息
 *  [aa] -> {1b -> 3e -> NULL}
 *  顶点信息
 *  [b] -> {NULL}
 *  顶点信息
 *  [d] -> {NULL}
 *  顶点信息
 *  [e] -> {NULL}
 * */
#include "adjmap.h"
int main(void) {
    ALGraph *g = (ALGraph *) malloc(sizeof(ALGraph));
    createGraph(g, 4, 5);
    display(g);
    printf("索引为2的顶点 %s\n",getVex(g, 2));
    putVex(g, "a", "aa");
    printf("将a顶点修改aa后查看结果 %s\n", getVex(g, locateVex(g,"aa")));
    printf("顶点c的第一个邻接点的位置和信息是 %d %s\n", fristAdjVex(g, "c"), getVex(g, fristAdjVex(g, "c")));
    printf("%d\n", nextAdjVex(g, "b", "c"));
    deleteVex(g,"c");
    display(g);
    printf("删除顶点后的弧还剩 %d个\n", g->arc);
    printf("新的插入顶点e是否成功%d\n",insertVex(g, "e"));
    printf("添加aa->e的一条弧是否成功:%d\n",insertArc(g, "aa", "e"));
    display(g);
    printf("删除aa->d之间的弧是否成功:%d\n", deleteArc(g, "aa", "d"));
    display(g);
    return 0;
}