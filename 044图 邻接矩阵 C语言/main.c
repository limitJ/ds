#include "adjmatrix.h"
/*
 * ���ݽṹ ͼ
 *  �ڽӾ���洢��ʾ��
 * QQ 582521582
 * QQȺ 322085520
 * */
int main(void) {
    AMGraph *g = (AMGraph *) malloc(sizeof(AMGraph));
    char v1[16], v2[16];
    printf("��˳��ѡ������ͼ,������,����ͼ,������\n");
    CreateGraph(g);
    Display(g);
    printf("�����¶��㣬�����붥���ֵ: ");
    scanf("%s",v1);
    InsertVex(g,v1);
    printf("�������¶����йصĻ���ߣ������뻡�����: ");
    int n = 0;
    scanf("%d",&n); // NOLINT(cert-err34-c)
    for(int k=0;k<n;k++) {
        printf("��������һ�����ֵ: ");
        scanf("%s",v2);
        if (g->kind <= 1) {
            //����ͼ
            printf("��������ͼ��������������һ����ķ���(0:��ͷ 1:��β): ");
            int j = 0;
            scanf("%d",&j); // NOLINT(cert-err34-c)
            if(j == 1) { // v2�ǻ�β
                InsertArc(g, v2, v1);
            }
            else { // v2�ǻ�ͷ
                InsertArc(g, v1, v2);
            }
        }else{
            //����ͼ
            InsertArc(g,v1,v2);
        }
    }
    Display(g); // ���ͼg
    DestroyGraph(g); // ����ͼg
    return 0;
}
