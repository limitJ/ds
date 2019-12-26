#include "adjmap.h"
/*
 * @param 图G  vexInfo顶点信息
 * @result 如果vexInfo存在 则返回在数组中的下标 否则返回-1
 * */
int locateVex(ALGraph* G,char vexInfo[8]){
    for (int i = 0; i < G->vex; ++i) {
        if (strcmp(G->vexarrs[i].vexinfo, vexInfo) == 0) {
            return i;
        }
    }
    return -1;
}

/*
 *@param 图G 数组下标index
 *@result 返回下标为index的顶点的信息
 * */
char* getVex(ALGraph* G,int index){
    assert(G != NULL);
    assert(index < G->vex);
    return G->vexarrs[index].vexinfo;
}
/*
 * @param 图G 顶点v
 * @result 返回顶点v的第一个邻节点信息 默认按照链表添加顺序返回第一个
 * */
int fristAdjVex(ALGraph* G, char v[8]){
    assert(G != NULL);
    int index = locateVex(G, v);
    assert(index!=-1);
    if (G->vexarrs[index].firstarc == NULL) {
        return -1;
    }
    return G->vexarrs[index].firstarc->index;
}

/*
 * @param 图G 顶点V 有关v的出度的其中一个顶点w
 * @result 返回w的后一个节点在图数组中的下标序号 如果w是最后一个节点 或v不存在出度 则返回-1
 * */
int nextAdjVex(ALGraph* G, char v[8],char w[8]){
    assert(G != NULL);
    int vindex = locateVex(G, v);
    ArcNode* element = G->vexarrs[vindex].firstarc;
    if(element == NULL){
        return -1;
    }
    for (;element!=NULL;element = element->nextarc) {
        if (strcmp(G->vexarrs[element->index].vexinfo, w) == 0) {
            if(element->nextarc!=NULL){
                return element->nextarc->index;
            }
        }
    }
    free(element);
    return -1;
}

/*
 *@param 顶点adjlist 弧信息节点
 *@result 在顶点后面添加弧节点信息
 * */
void addarcnode(AdjList adjList,ArcNode* arcNode){
    if (adjList->size == 0) {
        arcNode->nextarc = NULL;
        adjList->firstarc = arcNode;
        adjList->tailarc = adjList->firstarc;
    }else{
        arcNode->nextarc = NULL;
        adjList->tailarc->nextarc = arcNode;
        adjList->tailarc = arcNode;
    }
    adjList->size++;
}

/*
 *@parma G图 vex顶点数量 arc弧数量
 *@result 建立顶点信息 顶点为出度 生成每个顶点的链表弧信息
 * */
void createGraph(ALGraph* G,int vex,int arc){
    //有向图的重要性质 弧e和点n的关系要满足e = [0,n(n-1)]
    assert(arc>=0 && arc<=vex*(vex-1));
    assert(vex>=0 && arc>=0);
    assert(vex<=32);
    G->vex = vex;
    G->arc = arc;
    printf("请输入%d个有向图中顶点的信息！\n",vex);
    for (int i = 0; i < G->vex; ++i) {
        scanf("%s", G->vexarrs[i].vexinfo);
        G->vexarrs[i].firstarc = NULL;//初始化为NULL
        G->vexarrs[i].tailarc = NULL;
        G->vexarrs[i].size = 0;
    }
    printf("请输入%d个有向图中弧的信息(各不超过8各字符) 弧尾 弧头 权值\n",G->arc);
    for (int i = 0; i < G->arc; ++i) {
        char va[8],vb[8];
        int weight = 0;
        scanf("%s%s%d", va, vb, &weight); // NOLINT(cert-err34-c)
        int tail = locateVex(G, va);
        int head = locateVex(G, vb);
        assert(tail != -1 && head!=-1);
        ArcNode *arcNode = (ArcNode *) malloc(sizeof(ArcNode));
        arcNode->index = head;
        arcNode->weight = weight;
        addarcnode(&G->vexarrs[tail],arcNode);
    }
}

/*
 *@param 图G
 *@result 打印顶点信息 并打印每个顶点后面跟着的链表信息
 * */
void display(ALGraph *G){
    for (int i = 0; i < G->vex; ++i) {
        printf("顶点信息\n");
        printf("[%s] -> {", G->vexarrs[i].vexinfo);
        ArcNode* element = G->vexarrs[i].firstarc;
        if (element == NULL) {
            printf("NULL");//如果是NULL 说明没有指向
        }
        for (; element!=NULL; element=element->nextarc) {
            printf("%d%s -> ", element->index,G->vexarrs[element->index].vexinfo);
            if (element->nextarc == NULL) {
                printf("NULL");
            }
        }
        printf("}\n");
        free(element);
    }
}