/*
 * 图 BFS 广度优先遍历
 * QQ 582521582
 * QQ群 322085520
 * 作者水平有限 错误在所难免 欢迎阅者指正
 * 本程序运行环境 MinGW gcc8.3
 * 编译器 CLion2019.1
 * c标准 c11
 * 请勿在vs vc平台下运行 不支持
 * 程序测试用例如下
 * 请输入8个有向图中顶点的信息！
    v1 v2 v3 v4 v5 v6 v7 v8
    请输入8个有向图中弧的信息(各不超过8各字符) 弧尾 弧头 权值
    v1 v2 1
    v1 v3 1
    v2 v4 1
    v2 v5 1
    v5 v8 1
    v4 v8 1
    v3 v6 1
    v3 v7 1
    广度度优先遍历结果！
    v1 v2 v3 v4 v5 v6 v7 v8
 * */
#include "adjmap.h"
#include "queue.h"
bool visited[MAX_VEX_NUM] = {false};
void BFS(ALGraph* G);
int main(void) {
    ALGraph *g = (ALGraph *) malloc(sizeof(ALGraph));
    createGraph(g, 8, 8);//
    printf("广度度优先遍历结果！\n");
    BFS(g);
    printf("\n");
    return 0;
}
void BFS(ALGraph* G){
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    initQueue(queue);
    for (int v = 0; v < G->vex; ++v) {
        if (visited[v] == false) {//还没有访问过
            visited[v] = true;
            printf("%s ", getVex(G, v));
        }
        poll(queue, &G->vexarrs[v]);
        while (!isEmpty(queue)) {
            pop(queue);
            char* ch = getVex(G,v);
            for (int w = fristAdjVex(G, ch); w >= 0; w = nextAdjVex(G, getVex(G, v), getVex(G, w))) {
                if (visited[v] == false) {//还没有访问过
                    visited[v] = true;
                    printf("%s ", getVex(G, w));
                    poll(queue, &G->vexarrs[w]);
                }
            }
        }
    }
}