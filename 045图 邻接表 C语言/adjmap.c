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
 * @param 图G 顶点v 新顶点的值
 * @result 将顶点v的信息改成newv
 * */
bool putVex(ALGraph* G,char v[8],char newv[8]){
    assert(G != NULL);
    int index = locateVex(G, v);
    if (index == -1) {
        return false;
    } else{
        strcpy(G->vexarrs[index].vexinfo, newv);
    }
    return true;
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
 *@param 图G 顶点信息v
 *@result 将新顶点插入图G 不用考虑弧的有关信息 弧在insertArc函数中实现 如果插入失败 说明图容量不够返回false
 * */
bool insertVex(ALGraph* G,char v[8]){
    if (G->vex == MAX_VEX_NUM) {
        char e[256] = "图存储节点已到最大值,添加失败!";
        throwException(e);
        return false;
    }
    assert(G != NULL);
    strcpy(G->vexarrs[G->vex].vexinfo, v);
    G->vexarrs[G->vex].firstarc = NULL;
    G->vexarrs[G->vex].tailarc = NULL;
    G->vexarrs[G->vex].size = 0;
    G->vex++;
    return true;
}
/*
 * @paramm 图G v w是图中存在的2个顶点信息
 * @result 在有向网中添加vw之间的一条的弧 v是弧尾 w是弧头
 * */
bool insertArc(ALGraph* G,char v[8],char w[8]){
    assert(G != NULL);
    int vindex = locateVex(G, v);
    int windex = locateVex(G, w);
    if (vindex == -1 || windex == -1) {
        throwException("弧头或者弧尾不存在,添加弧失败\n");
        return false;
    }
    ArcNode *element  = G->vexarrs[vindex].firstarc;
    for (; element != NULL; element = element->nextarc) {
        if (strcmp(G->vexarrs[element->index].vexinfo, w) == 0) {
            throwException("弧已经存在,请勿重复添加!添加失败\n");
            return false;
        }
    }
    free(element);
    ArcNode *arcNode = (ArcNode *) malloc(sizeof(ArcNode));
    assert(arcNode!=NULL);
    G->vexarrs[vindex].size++;
    printf("请输入v w弧之间的权值weight\n");
    scanf("%d", &arcNode->weight);
    arcNode->nextarc = NULL;
    arcNode->index = windex;
    addarcnode(&G->vexarrs[vindex], arcNode);
    G->arc++;
    return true;
}

/*
 *@param 图G 顶点v
 *@result 删除G中的顶点v 以v为出度的弧直接删除 以v为入度的弧删除要修改有关的下标值 因为删除发生了数组元素移动
 * */
bool deleteVex(ALGraph* G,char v[8]){
    int vindex = locateVex(G, v);
    if (vindex == -1) {
        throwException("该图中没有该顶点信息");
        return false;
    }
    if (G->vex == 0) {
        throwException("空图 没有元素可删");
        return false;
    }
    ArcNode* element = G->vexarrs[vindex].firstarc;
    while (element != NULL) {
        G->vexarrs[vindex].size--;
        G->arc--;//弧的数量也要减
        ArcNode* old_element = element;
        element = element->nextarc;
        free(old_element);//销毁顶点后链接的弧信息
    }
    G->vexarrs[vindex].firstarc = NULL;
    G->vexarrs[vindex].tailarc = NULL;
    G->vex--;
    for (int i = vindex; i < G->vex; ++i) {
        G->vexarrs[i] = G->vexarrs[i+1];//删除该顶点后 将后面的元素前移
    }
    for (int i = 0; i < G->vex; ++i) {
        if (G->vexarrs[i].firstarc!=NULL && G->vexarrs[i].firstarc->index == vindex) {
            ArcNode* old = G->vexarrs[i].firstarc;
            G->vexarrs[i].firstarc = G->vexarrs[i].firstarc->nextarc;
            G->vexarrs[i].size--;
            G->arc--;
            if (G->vexarrs[i].size == 0) {
                G->vexarrs[i].firstarc = NULL;
                G->vexarrs[i].tailarc = NULL;
            }
            free(old);
            break;
        }
        ArcNode* temp = G->vexarrs[i].firstarc;
        while (temp != NULL) {
            if (temp->index > vindex) {
                temp->index--;
            }
            if (temp->nextarc != NULL && temp->nextarc->index == vindex) {
                ArcNode* old = temp;
                temp->nextarc = temp->nextarc->nextarc;
                if (temp->nextarc == NULL) {
                    G->vexarrs[i].tailarc = temp;
                }
                G->vexarrs[i].size--;
                G->arc--;
                free(old);
            }
            temp = temp->nextarc;
        }
        free(temp);
    }
    return true;
}

/*
 *@param 图G v w是存在于图中的2个顶点信息
 *@result 删除连接v w之间的弧 v是顶点弧尾信息 w是弧头
 * */
bool deleteArc(ALGraph* G, char v[8],char w[8]){
    assert(G != NULL);
    int vindex = locateVex(G, v);
    int windex = locateVex(G, w);
    if (vindex == -1 || windex == -1) {
        throwException("顶点信息不存在于图中,删除失败\n");
        return false;
    }
    ArcNode* element = G->vexarrs[vindex].firstarc;
    int loc = 0;
    for (; element != NULL; element = element->nextarc) {
        if (strcmp(G->vexarrs[element->index].vexinfo, w) == 0) {
            break;
        }
        loc++;
    }
    if (element == NULL) {
        throwException("2个顶点之间不存在弧关联,删除失败！\n");
        return false;
    }else{
        ArcNode* old = NULL;
        if (loc == 0) {
            old = G->vexarrs[vindex].firstarc;
            G->vexarrs[vindex].firstarc = G->vexarrs[vindex].firstarc->nextarc;
            G->vexarrs[vindex].size--;
            if (G->vexarrs[vindex].size == 0) {
                G->vexarrs[vindex].firstarc = NULL;
                G->vexarrs[vindex].tailarc = NULL;
            }
            G->arc--;
        }else{
            ArcNode* temp = G->vexarrs[vindex].firstarc;
            for (int i = 0; i < loc-1; ++i) {
                temp = temp->nextarc;
            }
            old = temp->nextarc;
            temp->nextarc = old->nextarc;
            if (temp->nextarc == NULL) {
                G->vexarrs[vindex].tailarc = temp;
            }
            G->arc--;
            G->vexarrs[vindex].size--;
        }
        free(old);
    }
    return true;
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