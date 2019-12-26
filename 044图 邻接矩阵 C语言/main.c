#include "adjmatrix.h"
/*
 * 数据结构 图
 *  邻接矩阵存储表示法
 * QQ 582521582
 * QQ群 322085520
 * */
int main(void) {
    AMGraph *g = (AMGraph *) malloc(sizeof(AMGraph));
    char v1[16], v2[16];
    printf("请顺序选择有向图,有向网,无向图,无向网\n");
    CreateGraph(g);
    Display(g);
    printf("插入新顶点，请输入顶点的值: ");
    scanf("%s",v1);
    InsertVex(g,v1);
    printf("插入与新顶点有关的弧或边，请输入弧或边数: ");
    int n = 0;
    scanf("%d",&n); // NOLINT(cert-err34-c)
    for(int k=0;k<n;k++) {
        printf("请输入另一顶点的值: ");
        scanf("%s",v2);
        if (g->kind <= 1) {
            //有向图
            printf("对于有向图或网，请输入另一顶点的方向(0:弧头 1:弧尾): ");
            int j = 0;
            scanf("%d",&j); // NOLINT(cert-err34-c)
            if(j == 1) { // v2是弧尾
                InsertArc(g, v2, v1);
            }
            else { // v2是弧头
                InsertArc(g, v1, v2);
            }
        }else{
            //无向图
            InsertArc(g,v1,v2);
        }
    }
    Display(g); // 输出图g
    DestroyGraph(g); // 销毁图g
    return 0;
}
