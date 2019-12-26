//
// Created by QQ 582521582 on 2019/5/16.
//
#include "adjmatrix.h"
void CreateGraph(AMGraph* G){ // ��������(�ڽӾ���)��ʾ��������ͼG���㷨7.1��
    printf("������ͼG������(����ͼ:0,������:1,����ͼ:2,������:3): ");
    scanf("%d",&G->kind); // NOLINT(cert-err34-c)
    switch(G->kind){
        case DG:
            CreateDG(G); // ��������ͼ
            break;
        case DN:
            CreateDN(G); // ����������
            break;
        case UDG:
            CreateUDG(G); // ��������ͼ
            break;
        case UDN:
            CreateUDN(G); // ����������
            break;
        default:
            exit(-1);
    }
}

int LocateVex(AMGraph* G,char u[16]){ // ��ʼ������ͼG���ڣ�u��G�ж�������ͬ����
    // �����������G�д��ڶ���u���򷵻ظö�����ͼ��λ�ã����򷵻�-1
    for (int i = 0; i < G->vex; ++i) {
        if(strcmp(u,G->vexarrs[i])==0){
            return i;
        }
    }
    return -1;
}

void CreateDG(AMGraph* G){ // ��������(�ڽӾ���)��ʾ������������ͼG
    int IncInfo = 0;
    char va[16],vb[16];
    printf("����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
    scanf("%d%d%d",&G->vex,&G->arc,&IncInfo); // NOLINT(cert-err34-c)
    printf("������%d�������ֵ(<5���ַ�):\n",G->vex);
    for(int i=0;i<G->vex;++i) { // ���춥������
        scanf("%s", G->vexarrs[i]);
    }
    for(int i=0;i<G->vex;++i) { // ��ʼ���ڽӾ���
        for (int j = 0; j < G->vex; ++j) {
            G->adjmat[i][j].adj = 0; // ͼ
            G->adjmat[i][j].info = NULL;
        }
    }
    printf("������%d�����Ļ�β ��ͷ(�Կո���Ϊ���): \n",G->arc);
    for(int k=0;k<G->arc;++k){
        scanf("%s%s%*c",va,vb);  // %*c�Ե��س���
        int i=LocateVex(G,va);
        int j=LocateVex(G,vb);
        G->adjmat[i][j].adj=1; // ����ͼ
        if(IncInfo!=0){
            char s[32];
            printf("������û��������Ϣ(<32���ַ�): ");
            gets(s);
            int len = strlen(s);
            if(len!=0){
                G->adjmat[i][j].info=(char*)malloc((len+1)*sizeof(char)); // ����
                strcpy(G->adjmat[i][j].info,s);
            }
        }
    }
    G->kind=DG;
}

void CreateDN(AMGraph* G){ // ��������(�ڽӾ���)��ʾ��������������G
    int IncInfo = 0;
    char va[16],vb[16];
    printf("������������G�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
    scanf("%d%d%d",&G->vex,&G->arc,&IncInfo); // NOLINT(cert-err34-c)
    printf("������%d�������ֵ(<16���ַ�):\n",G->vex);
    for(int i = 0;i<G->vex;++i) { // ���춥������
        scanf("%s", G->vexarrs[i]);
    }
    for(int i=0;i<G->vex;++i) // ��ʼ���ڽӾ���
    for(int j=0;j<G->vex;++j){
        G->adjmat[i][j].adj = 0XFFFFFFF; // ��
        G->adjmat[i][j].info=NULL;
    }
    printf("������%d�����Ļ�β ��ͷ Ȩֵ(�Կո���Ϊ���): \n",G->arc); // NOLINT(readability-misleading-indentation)
    for(int k=0;k<G->arc;++k){
        int w = 0;
    scanf("%s%s%d%*c",va,vb,&w);  // %*c�Ե��س��� NOLINT(cert-err34-c)
    int i=LocateVex(G,va);
    int j=LocateVex(G,vb);
    G->adjmat[i][j].adj=w; // ������
    if(IncInfo){
        char s[32];
        printf("������û��������Ϣ(<32���ַ�): ");
        gets(s);
        int len = strlen(s);
        if(len!=0){
        G->adjmat[i][j].info=(char*)malloc((len+1)*sizeof(char)); // ����
        strcpy(G->adjmat[i][j].info,s);
        }
    }
}
    G->kind=DN;
}

void CreateUDG(AMGraph* G){ // ��������(�ڽӾ���)��ʾ������������ͼG
    int IncInfo = 0;
    char va[16],vb[16];
    printf("����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
    scanf("%d%d%d",&G->vex,&G->arc,&IncInfo); // NOLINT(cert-err34-c)
    printf("������%d�������ֵ(<16���ַ�):\n",G->vex);
    for(int i = 0;i<G->vex;++i) { // ���춥������
        scanf("%s", G->vexarrs[i]);
    }
    for(int i=0;i<G->vex;++i) // ��ʼ���ڽӾ���
        for(int j=0;j<G->vex;++j){
            G->adjmat[i][j].adj = 0; // ����ͼ
            G->adjmat[i][j].info=NULL;
        }
    printf("������%d���ߵĶ���1 ����2(�Կո���Ϊ���): \n",G->arc);
    for(int k=0;k<G->arc;++k){
        scanf("%s%s%*c",va,vb); // %*c�Ե��س���
        int i=LocateVex(G,va);
        int j=LocateVex(G,vb);
        G->adjmat[i][j].adj=G->adjmat[j][i].adj=1; // ����ͼ�ھ�����һ������Գƹ�ϵ
        if(IncInfo){
            char s[32];
            printf("������ñߵ������Ϣ(<32���ַ�): ");
            gets(s);
            int len = strlen(s);
            if(len!=0){
                G->adjmat[i][j].info=G->adjmat[j][i].info=(char*)malloc((len+1)*sizeof(char));
                // ��������ָ��ָ��ͬһ����Ϣ
                strcpy(G->adjmat[i][j].info,s);
            }
        }
    }
    G->kind=UDG;
}
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
void CreateUDN(AMGraph* G){ // ��������(�ڽӾ���)��ʾ��������������G
    int IncInfo = 0;
    char va[16],vb[16];
    printf("������������G�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
    scanf("%d%d%d",&G->vex,&G->arc,&IncInfo); // NOLINT(cert-err34-c)
    printf("������%d�������ֵ(<16���ַ�):\n",G->vex);
    for(int i = 0;i<G->vex;++i) { // ���춥������
        scanf("%s", G->vexarrs[i]);
    }
    for(int i=0;i<G->vex;++i) // ��ʼ���ڽӾ���
        for(int j=0;j<G->vex;++j){
            G->adjmat[i][j].adj = 0XFFFFFFF; // ������
            G->adjmat[i][j].info=NULL;
        }
    printf("������%d���ߵĶ���1 ����2 Ȩֵ(�Կո���Ϊ���): \n",G->arc);
    for(int k=0;k<G->arc;++k){
        int w = 0;
        scanf("%s%s%d%*c",va,vb,&w); // %*c�Ե��س���
        int i=LocateVex(G,va);
        int j=LocateVex(G,vb);
        G->adjmat[i][j].adj=G->adjmat[j][i].adj=w; // ����ͼ�ھ�����һ������Գƹ�ϵ
        if(IncInfo){
            char s[32];
            printf("������ñߵ������Ϣ(<32���ַ�): ");
            gets(s);
            int len = strlen(s);
            if(len!=0){
                G->adjmat[i][j].info=G->adjmat[j][i].info=(char*)malloc((len+1)*sizeof(char));
                // ��������ָ��ָ��ͬһ����Ϣ
                strcpy(G->adjmat[i][j].info,s);
            }
        }
    }
    G->kind=UDN;
}
#pragma clang diagnostic pop


void Display(AMGraph* G){ // ����ڽӾ���洢��ʾ��ͼG
    int i,j;
    char s[8];
    switch(G->kind)
    {
        case DG: strcpy(s,"����ͼ");
            break;
        case DN: strcpy(s,"������");
            break;
        case UDG:strcpy(s,"����ͼ");
            break;
        case UDN:strcpy(s,"������");
    }
    printf("%d������%d���߻򻡵�%s������������: ",G->vex,G->arc,s);
    for(i=0;i<G->vex;++i) { // ���G.vexs
        printf("%s ", G->vexarrs[i]);
    }
    printf("\nG.arcs.adj:\n"); // ���G.arcs.adj
    for(i=0;i<G->vex;i++){
        for(j=0;j<G->vex;j++) {
            printf("%d ", G->adjmat[i][j].adj);
        }
        printf("\n");
    }
    printf("G.arcs.info:\n"); // ���G.arcs.info
    printf("����1(��β) ����2(��ͷ) �ñ߻򻡵���Ϣ��\n");
    for(i=0;i<G->vex;i++)
        if(G->kind<2){ // ����
            for(j=0;j<G->vex;j++) {
                if (G->adjmat[i][j].info) {
                    printf("%5s %s     %s\n", G->vexarrs[i], G->vexarrs[j], G->adjmat[i][j].info);
                }
            }
        }
        else { // ����,���������
            for (j = i + 1; j < G->vex; j++) {
                if (G->adjmat[i][j].info)
                    printf("%5s %s     %s\n", G->vexarrs[i], G->vexarrs[j], G->adjmat[i][j].info);
            }
        }
}

void InsertVex(AMGraph* G,char v[16]){ // ��ʼ������ͼG���ڣ�v��ͼG�ж�������ͬ����
    strcpy(G->vexarrs[G->vex],v); // �����¶�������
    for(int i=0;i<=G->vex;i++){
        G->adjmat[G->vex][i].adj=G->adjmat[i][G->vex].adj=G->kind%2==0?0:0XFFFFFFF;
        G->adjmat[G->vex][i].info=G->adjmat[i][G->vex].info=NULL; // ��ʼ�������Ϣָ��
    }
    G->vex++; // ͼG�Ķ�������1
}

bool InsertArc(AMGraph* G,char v[16],char w[16]){ // ��ʼ������ͼG���ڣ�v��w��G����������
//��G������<v,w>����G������ģ�������Գƻ�<w,v>
    char s[8];
    int v1=LocateVex(G,v); // β
    int w1=LocateVex(G,w); // ͷ
    if(v1<0||w1<0){
        throwException("Խ��");
        return false;
    }
    G->arc++; // ���������1
    if(G->kind%2!=0){ // ��
    printf("������˻���ߵ�Ȩֵ: ");
    scanf("%d",&G->adjmat[v1][w1].adj);
    }else { // ͼ
        G->adjmat[v1][w1].adj = 1;
    }
    int i = 0;
    printf("�Ƿ��иû���ߵ������Ϣ(0:�� 1:��): ");
    scanf("%d%*c",&i);
    if(i!=0){
        printf("������û���ߵ������Ϣ(<16���ַ�)��");
        gets(s);
        int len = strlen(s);
        if(len != 0){
            G->adjmat[v1][w1].info=(char*)malloc((len+1)*sizeof(char));
            strcpy(G->adjmat[v1][w1].info,s);
        }
    }
    if(G->kind>1){ // ����
        G->adjmat[w1][v1].adj=G->adjmat[v1][w1].adj;
        G->adjmat[w1][v1].info=G->adjmat[v1][w1].info; // ָ��ͬһ�������Ϣ
    }
    return true;
}


void DestroyGraph(AMGraph* G){ // ��ʼ������ͼG���ڡ��������������ͼG
int i,j,k=0;
    for(i=0;i<G->vex;i++){ // �ͷŻ���ߵ������Ϣ(����еĻ�)
        if(G->kind<2){ // ����
            for(j=0;j<G->vex;j++){
                if(G->adjmat[i][j].adj!=G->kind%2==0?0:0XFFFFFFF) // �л�
                    if(G->adjmat[i][j].info) // �������Ϣ
                    {
                        free(G->adjmat[i][j].info);
                        G->adjmat[i][j].info=NULL;
                    }
            }
        }else{ // ����
            for (j = i + 1; j < G->vex; j++) // ֻ��������
                if (G->adjmat[i][j].adj != G->kind%2==0?0:0XFFFFFFF) // �б�
                    if (G->adjmat[i][j].info) // �������Ϣ
                    {
                        free(G->adjmat[i][j].info);
                        G->adjmat[i][j].info = G->adjmat[j][i].info = NULL;
                    }
        }
    }
    G->vex=0; // ������Ϊ0
    G->arc=0; // ����Ϊ0
}