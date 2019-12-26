#include "adjmap.h"
/*
 * @param ͼG  vexInfo������Ϣ
 * @result ���vexInfo���� �򷵻��������е��±� ���򷵻�-1
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
 *@param ͼG �����±�index
 *@result �����±�Ϊindex�Ķ������Ϣ
 * */
char* getVex(ALGraph* G,int index){
    assert(G != NULL);
    assert(index < G->vex);
    return G->vexarrs[index].vexinfo;
}
/*
 * @param ͼG ����v
 * @result ���ض���v�ĵ�һ���ڽڵ���Ϣ Ĭ�ϰ����������˳�򷵻ص�һ��
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
 * @param ͼG ����V �й�v�ĳ��ȵ�����һ������w
 * @result ����w�ĺ�һ���ڵ���ͼ�����е��±���� ���w�����һ���ڵ� ��v�����ڳ��� �򷵻�-1
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
 *@param ����adjlist ����Ϣ�ڵ�
 *@result �ڶ��������ӻ��ڵ���Ϣ
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
 *@parma Gͼ vex�������� arc������
 *@result ����������Ϣ ����Ϊ���� ����ÿ�������������Ϣ
 * */
void createGraph(ALGraph* G,int vex,int arc){
    //����ͼ����Ҫ���� ��e�͵�n�Ĺ�ϵҪ����e = [0,n(n-1)]
    assert(arc>=0 && arc<=vex*(vex-1));
    assert(vex>=0 && arc>=0);
    assert(vex<=32);
    G->vex = vex;
    G->arc = arc;
    printf("������%d������ͼ�ж������Ϣ��\n",vex);
    for (int i = 0; i < G->vex; ++i) {
        scanf("%s", G->vexarrs[i].vexinfo);
        G->vexarrs[i].firstarc = NULL;//��ʼ��ΪNULL
        G->vexarrs[i].tailarc = NULL;
        G->vexarrs[i].size = 0;
    }
    printf("������%d������ͼ�л�����Ϣ(��������8���ַ�) ��β ��ͷ Ȩֵ\n",G->arc);
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
 *@param ͼG
 *@result ��ӡ������Ϣ ����ӡÿ�����������ŵ�������Ϣ
 * */
void display(ALGraph *G){
    for (int i = 0; i < G->vex; ++i) {
        printf("������Ϣ\n");
        printf("[%s] -> {", G->vexarrs[i].vexinfo);
        ArcNode* element = G->vexarrs[i].firstarc;
        if (element == NULL) {
            printf("NULL");//�����NULL ˵��û��ָ��
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