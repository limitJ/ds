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
 * @param ͼG ����v �¶����ֵ
 * @result ������v����Ϣ�ĳ�newv
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
 *@param ͼG ������Ϣv
 *@result ���¶������ͼG ���ÿ��ǻ����й���Ϣ ����insertArc������ʵ�� �������ʧ�� ˵��ͼ������������false
 * */
bool insertVex(ALGraph* G,char v[8]){
    if (G->vex == MAX_VEX_NUM) {
        char e[256] = "ͼ�洢�ڵ��ѵ����ֵ,���ʧ��!";
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
 * @paramm ͼG v w��ͼ�д��ڵ�2��������Ϣ
 * @result �������������vw֮���һ���Ļ� v�ǻ�β w�ǻ�ͷ
 * */
bool insertArc(ALGraph* G,char v[8],char w[8]){
    assert(G != NULL);
    int vindex = locateVex(G, v);
    int windex = locateVex(G, w);
    if (vindex == -1 || windex == -1) {
        throwException("��ͷ���߻�β������,��ӻ�ʧ��\n");
        return false;
    }
    ArcNode *element  = G->vexarrs[vindex].firstarc;
    for (; element != NULL; element = element->nextarc) {
        if (strcmp(G->vexarrs[element->index].vexinfo, w) == 0) {
            throwException("���Ѿ�����,�����ظ����!���ʧ��\n");
            return false;
        }
    }
    free(element);
    ArcNode *arcNode = (ArcNode *) malloc(sizeof(ArcNode));
    assert(arcNode!=NULL);
    G->vexarrs[vindex].size++;
    printf("������v w��֮���Ȩֵweight\n");
    scanf("%d", &arcNode->weight);
    arcNode->nextarc = NULL;
    arcNode->index = windex;
    addarcnode(&G->vexarrs[vindex], arcNode);
    G->arc++;
    return true;
}

/*
 *@param ͼG ����v
 *@result ɾ��G�еĶ���v ��vΪ���ȵĻ�ֱ��ɾ�� ��vΪ��ȵĻ�ɾ��Ҫ�޸��йص��±�ֵ ��Ϊɾ������������Ԫ���ƶ�
 * */
bool deleteVex(ALGraph* G,char v[8]){
    int vindex = locateVex(G, v);
    if (vindex == -1) {
        throwException("��ͼ��û�иö�����Ϣ");
        return false;
    }
    if (G->vex == 0) {
        throwException("��ͼ û��Ԫ�ؿ�ɾ");
        return false;
    }
    ArcNode* element = G->vexarrs[vindex].firstarc;
    while (element != NULL) {
        G->vexarrs[vindex].size--;
        G->arc--;//��������ҲҪ��
        ArcNode* old_element = element;
        element = element->nextarc;
        free(old_element);//���ٶ�������ӵĻ���Ϣ
    }
    G->vexarrs[vindex].firstarc = NULL;
    G->vexarrs[vindex].tailarc = NULL;
    G->vex--;
    for (int i = vindex; i < G->vex; ++i) {
        G->vexarrs[i] = G->vexarrs[i+1];//ɾ���ö���� �������Ԫ��ǰ��
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
 *@param ͼG v w�Ǵ�����ͼ�е�2��������Ϣ
 *@result ɾ������v w֮��Ļ� v�Ƕ��㻡β��Ϣ w�ǻ�ͷ
 * */
bool deleteArc(ALGraph* G, char v[8],char w[8]){
    assert(G != NULL);
    int vindex = locateVex(G, v);
    int windex = locateVex(G, w);
    if (vindex == -1 || windex == -1) {
        throwException("������Ϣ��������ͼ��,ɾ��ʧ��\n");
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
        throwException("2������֮�䲻���ڻ�����,ɾ��ʧ�ܣ�\n");
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