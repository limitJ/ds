//
// Created by QQ 582521582 on 2019/5/16.
//
#include "adjmatrix.h"
void CreateGraph(AMGraph* G){ // 采用数组(邻接矩阵)表示法，构造图G。算法7.1改
    printf("请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3): ");
    scanf("%d",&G->kind); // NOLINT(cert-err34-c)
    switch(G->kind){
        case DG:
            CreateDG(G); // 构造有向图
            break;
        case DN:
            CreateDN(G); // 构造有向网
            break;
        case UDG:
            CreateUDG(G); // 构造无向图
            break;
        case UDN:
            CreateUDN(G); // 构造无向网
            break;
        default:
            exit(-1);
    }
}

int LocateVex(AMGraph* G,char u[16]){ // 初始条件：图G存在，u和G中顶点有相同特征
    // 操作结果：若G中存在顶点u，则返回该顶点在图中位置；否则返回-1
    for (int i = 0; i < G->vex; ++i) {
        if(strcmp(u,G->vexarrs[i])==0){
            return i;
        }
    }
    return -1;
}

void CreateDG(AMGraph* G){ // 采用数组(邻接矩阵)表示法，构造有向图G
    int IncInfo = 0;
    char va[16],vb[16];
    printf("请输入有向图G的顶点数,弧数,弧是否含其它信息(是:1,否:0): ");
    scanf("%d%d%d",&G->vex,&G->arc,&IncInfo); // NOLINT(cert-err34-c)
    printf("请输入%d个顶点的值(<5个字符):\n",G->vex);
    for(int i=0;i<G->vex;++i) { // 构造顶点向量
        scanf("%s", G->vexarrs[i]);
    }
    for(int i=0;i<G->vex;++i) { // 初始化邻接矩阵
        for (int j = 0; j < G->vex; ++j) {
            G->adjmat[i][j].adj = 0; // 图
            G->adjmat[i][j].info = NULL;
        }
    }
    printf("请输入%d条弧的弧尾 弧头(以空格作为间隔): \n",G->arc);
    for(int k=0;k<G->arc;++k){
        scanf("%s%s%*c",va,vb);  // %*c吃掉回车符
        int i=LocateVex(G,va);
        int j=LocateVex(G,vb);
        G->adjmat[i][j].adj=1; // 有向图
        if(IncInfo!=0){
            char s[32];
            printf("请输入该弧的相关信息(<32个字符): ");
            gets(s);
            int len = strlen(s);
            if(len!=0){
                G->adjmat[i][j].info=(char*)malloc((len+1)*sizeof(char)); // 有向
                strcpy(G->adjmat[i][j].info,s);
            }
        }
    }
    G->kind=DG;
}

void CreateDN(AMGraph* G){ // 采用数组(邻接矩阵)表示法，构造有向网G
    int IncInfo = 0;
    char va[16],vb[16];
    printf("请输入有向网G的顶点数,弧数,弧是否含其它信息(是:1,否:0): ");
    scanf("%d%d%d",&G->vex,&G->arc,&IncInfo); // NOLINT(cert-err34-c)
    printf("请输入%d个顶点的值(<16个字符):\n",G->vex);
    for(int i = 0;i<G->vex;++i) { // 构造顶点向量
        scanf("%s", G->vexarrs[i]);
    }
    for(int i=0;i<G->vex;++i) // 初始化邻接矩阵
    for(int j=0;j<G->vex;++j){
        G->adjmat[i][j].adj = 0XFFFFFFF; // 网
        G->adjmat[i][j].info=NULL;
    }
    printf("请输入%d条弧的弧尾 弧头 权值(以空格作为间隔): \n",G->arc); // NOLINT(readability-misleading-indentation)
    for(int k=0;k<G->arc;++k){
        int w = 0;
    scanf("%s%s%d%*c",va,vb,&w);  // %*c吃掉回车符 NOLINT(cert-err34-c)
    int i=LocateVex(G,va);
    int j=LocateVex(G,vb);
    G->adjmat[i][j].adj=w; // 有向网
    if(IncInfo){
        char s[32];
        printf("请输入该弧的相关信息(<32个字符): ");
        gets(s);
        int len = strlen(s);
        if(len!=0){
        G->adjmat[i][j].info=(char*)malloc((len+1)*sizeof(char)); // 有向
        strcpy(G->adjmat[i][j].info,s);
        }
    }
}
    G->kind=DN;
}

void CreateUDG(AMGraph* G){ // 采用数组(邻接矩阵)表示法，构造无向图G
    int IncInfo = 0;
    char va[16],vb[16];
    printf("请输入无向图G的顶点数,边数,边是否含其它信息(是:1,否:0): ");
    scanf("%d%d%d",&G->vex,&G->arc,&IncInfo); // NOLINT(cert-err34-c)
    printf("请输入%d个顶点的值(<16个字符):\n",G->vex);
    for(int i = 0;i<G->vex;++i) { // 构造顶点向量
        scanf("%s", G->vexarrs[i]);
    }
    for(int i=0;i<G->vex;++i) // 初始化邻接矩阵
        for(int j=0;j<G->vex;++j){
            G->adjmat[i][j].adj = 0; // 无向图
            G->adjmat[i][j].info=NULL;
        }
    printf("请输入%d条边的顶点1 顶点2(以空格作为间隔): \n",G->arc);
    for(int k=0;k<G->arc;++k){
        scanf("%s%s%*c",va,vb); // %*c吃掉回车符
        int i=LocateVex(G,va);
        int j=LocateVex(G,vb);
        G->adjmat[i][j].adj=G->adjmat[j][i].adj=1; // 无向图在矩阵中一定满足对称关系
        if(IncInfo){
            char s[32];
            printf("请输入该边的相关信息(<32个字符): ");
            gets(s);
            int len = strlen(s);
            if(len!=0){
                G->adjmat[i][j].info=G->adjmat[j][i].info=(char*)malloc((len+1)*sizeof(char));
                // 无向，两个指针指向同一个信息
                strcpy(G->adjmat[i][j].info,s);
            }
        }
    }
    G->kind=UDG;
}
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
void CreateUDN(AMGraph* G){ // 采用数组(邻接矩阵)表示法，构造无向网G
    int IncInfo = 0;
    char va[16],vb[16];
    printf("请输入无向网G的顶点数,边数,边是否含其它信息(是:1,否:0): ");
    scanf("%d%d%d",&G->vex,&G->arc,&IncInfo); // NOLINT(cert-err34-c)
    printf("请输入%d个顶点的值(<16个字符):\n",G->vex);
    for(int i = 0;i<G->vex;++i) { // 构造顶点向量
        scanf("%s", G->vexarrs[i]);
    }
    for(int i=0;i<G->vex;++i) // 初始化邻接矩阵
        for(int j=0;j<G->vex;++j){
            G->adjmat[i][j].adj = 0XFFFFFFF; // 无向网
            G->adjmat[i][j].info=NULL;
        }
    printf("请输入%d条边的顶点1 顶点2 权值(以空格作为间隔): \n",G->arc);
    for(int k=0;k<G->arc;++k){
        int w = 0;
        scanf("%s%s%d%*c",va,vb,&w); // %*c吃掉回车符
        int i=LocateVex(G,va);
        int j=LocateVex(G,vb);
        G->adjmat[i][j].adj=G->adjmat[j][i].adj=w; // 无向图在矩阵中一定满足对称关系
        if(IncInfo){
            char s[32];
            printf("请输入该边的相关信息(<32个字符): ");
            gets(s);
            int len = strlen(s);
            if(len!=0){
                G->adjmat[i][j].info=G->adjmat[j][i].info=(char*)malloc((len+1)*sizeof(char));
                // 无向，两个指针指向同一个信息
                strcpy(G->adjmat[i][j].info,s);
            }
        }
    }
    G->kind=UDN;
}
#pragma clang diagnostic pop


void Display(AMGraph* G){ // 输出邻接矩阵存储表示的图G
    int i,j;
    char s[8];
    switch(G->kind)
    {
        case DG: strcpy(s,"有向图");
            break;
        case DN: strcpy(s,"有向网");
            break;
        case UDG:strcpy(s,"无向图");
            break;
        case UDN:strcpy(s,"无向网");
    }
    printf("%d个顶点%d条边或弧的%s。顶点依次是: ",G->vex,G->arc,s);
    for(i=0;i<G->vex;++i) { // 输出G.vexs
        printf("%s ", G->vexarrs[i]);
    }
    printf("\nG.arcs.adj:\n"); // 输出G.arcs.adj
    for(i=0;i<G->vex;i++){
        for(j=0;j<G->vex;j++) {
            printf("%d ", G->adjmat[i][j].adj);
        }
        printf("\n");
    }
    printf("G.arcs.info:\n"); // 输出G.arcs.info
    printf("顶点1(弧尾) 顶点2(弧头) 该边或弧的信息：\n");
    for(i=0;i<G->vex;i++)
        if(G->kind<2){ // 有向
            for(j=0;j<G->vex;j++) {
                if (G->adjmat[i][j].info) {
                    printf("%5s %s     %s\n", G->vexarrs[i], G->vexarrs[j], G->adjmat[i][j].info);
                }
            }
        }
        else { // 无向,输出上三角
            for (j = i + 1; j < G->vex; j++) {
                if (G->adjmat[i][j].info)
                    printf("%5s %s     %s\n", G->vexarrs[i], G->vexarrs[j], G->adjmat[i][j].info);
            }
        }
}

void InsertVex(AMGraph* G,char v[16]){ // 初始条件：图G存在，v和图G中顶点有相同特征
    strcpy(G->vexarrs[G->vex],v); // 构造新顶点向量
    for(int i=0;i<=G->vex;i++){
        G->adjmat[G->vex][i].adj=G->adjmat[i][G->vex].adj=G->kind%2==0?0:0XFFFFFFF;
        G->adjmat[G->vex][i].info=G->adjmat[i][G->vex].info=NULL; // 初始化相关信息指针
    }
    G->vex++; // 图G的顶点数加1
}

bool InsertArc(AMGraph* G,char v[16],char w[16]){ // 初始条件：图G存在，v和w是G中两个顶点
//在G中增添弧<v,w>，若G是无向的，则还增添对称弧<w,v>
    char s[8];
    int v1=LocateVex(G,v); // 尾
    int w1=LocateVex(G,w); // 头
    if(v1<0||w1<0){
        throwException("越界");
        return false;
    }
    G->arc++; // 弧或边数加1
    if(G->kind%2!=0){ // 网
    printf("请输入此弧或边的权值: ");
    scanf("%d",&G->adjmat[v1][w1].adj);
    }else { // 图
        G->adjmat[v1][w1].adj = 1;
    }
    int i = 0;
    printf("是否有该弧或边的相关信息(0:无 1:有): ");
    scanf("%d%*c",&i);
    if(i!=0){
        printf("请输入该弧或边的相关信息(<16个字符)：");
        gets(s);
        int len = strlen(s);
        if(len != 0){
            G->adjmat[v1][w1].info=(char*)malloc((len+1)*sizeof(char));
            strcpy(G->adjmat[v1][w1].info,s);
        }
    }
    if(G->kind>1){ // 无向
        G->adjmat[w1][v1].adj=G->adjmat[v1][w1].adj;
        G->adjmat[w1][v1].info=G->adjmat[v1][w1].info; // 指向同一个相关信息
    }
    return true;
}


void DestroyGraph(AMGraph* G){ // 初始条件：图G存在。操作结果：销毁图G
int i,j,k=0;
    for(i=0;i<G->vex;i++){ // 释放弧或边的相关信息(如果有的话)
        if(G->kind<2){ // 有向
            for(j=0;j<G->vex;j++){
                if(G->adjmat[i][j].adj!=G->kind%2==0?0:0XFFFFFFF) // 有弧
                    if(G->adjmat[i][j].info) // 有相关信息
                    {
                        free(G->adjmat[i][j].info);
                        G->adjmat[i][j].info=NULL;
                    }
            }
        }else{ // 无向
            for (j = i + 1; j < G->vex; j++) // 只查上三角
                if (G->adjmat[i][j].adj != G->kind%2==0?0:0XFFFFFFF) // 有边
                    if (G->adjmat[i][j].info) // 有相关信息
                    {
                        free(G->adjmat[i][j].info);
                        G->adjmat[i][j].info = G->adjmat[j][i].info = NULL;
                    }
        }
    }
    G->vex=0; // 顶点数为0
    G->arc=0; // 边数为0
}