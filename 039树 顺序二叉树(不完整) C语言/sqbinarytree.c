//
// Created by qq 582521582 on 2019/4/22.
//
#include "sqbinarytree.h"
void InitBiTree(int* T){ // ����ն�����T����ΪT��������
    //pass Ϊ�˷��� main����ֱ�������������� �Ͳ���Ҫ��ʼ����
    printf("��ʼ���ɹ���");
}

void CreateBiTree(int* T){

    for(int i=1;i<MAX_TREE_SIZE;i++)
        if(T[(i+1)/2-1]==0&&T[i]!=0) // �˽��(����)��˫���Ҳ��Ǹ�
        {
           printf("������˫�׵ķǸ����%d\n",T[i]);
           exit(-1);
        }
}

bool isEmpty(int* T){ // ��ʼ������������T���ڡ������������TΪ�ն��������򷵻�TRUE������FALSE
    return 0 == T[0];//�ܼ� ���ڵ�Ϊ�� ��������϶�Ϊ��
}

int Depth(int* T){ // ��ʼ������������T���ڡ��������������T�����
    int i,j=-1;
    for(i=MAX_TREE_SIZE-1;i>=0;i--) { // �ҵ����һ�����
        if (T[i] != 0) {
            break;
        }
    }
    i++;
    do {
        j++;
    }while(i>=pow(2,j)); //���ǿ��ڵڼ��� ��i�������T�е��±�Χ��2^(i-1) - 1 ~ 2^i - 2֮��
    return j;
}

int Root(int* T){ // ��ʼ������������T���ڡ������������T���գ�
    if(isEmpty(T)) { // T��
        return -1;
    }
    return T[0];
}

int Value(int* T,Pos e)
{ // ��ʼ������������T���ڣ�e��T��ĳ�����(��λ��)
    // ������������ش���λ��e(��,�������)�Ľ���ֵ
    return T[(int)(pow(2,e.level-1)+e.order-2)];
}

bool Assign(int* T,Pos e,int value)
{ // ��ʼ������������T���ڣ�e��T��ĳ�����(��λ��)
    // ���������������λ��e(��,�������)�Ľ�㸳��ֵvalue
    int i=(int)(pow(2,e.level-1)+e.order-2); // ���㡢�������תΪ��������
    if(value!=0&&T[(i+1)/2-1]==0) { // ��Ҷ�Ӹ��ǿ�ֵ��˫��Ϊ��
        return false;
    }else if(value==0&&(T[i*2+1]!=0||T[i*2+2]!=0)) { //  ��˫�׸���ֵ����Ҷ��(����)
        return false;
    }
    T[i]=value;
    return true;
}

int Parent(int* T,int e)
{ // ��ʼ������������T���ڣ�e��T��ĳ�����
    // �����������e��T�ķǸ���㣬�򷵻�����˫�ף����򷵻أ���0��
    int i;
    if(T[0]==0) { // ����
        return 0;
    }
    for(i=1;i<MAX_TREE_SIZE;i++) {
        if (T[i] == e) { // �ҵ�e
            return T[(i + 1) / 2 - 1];
        }
    }
    return 0; // û�ҵ�e
}

int LeftChild(int* T,int e)
{ // ��ʼ������������T���ڣ�e��T��ĳ����㡣�������������e�����ӡ���e������,�򷵻�"��"
    int i;
    if(T[0]==0) { // ����
        return 0;
    }
    for(i=0;i<MAX_TREE_SIZE;i++) {
        if (T[i] == e) { // �ҵ�e
            return T[i * 2 + 1];
        }
    }
    return 0; // û�ҵ�e
}

int RightChild(int* T,int e)
{ // ��ʼ������������T���ڣ�e��T��ĳ����㡣�������������e���Һ��ӡ���e���Һ���,�򷵻�"��"
    int i;
    if(T[0]==0) { // ����
        return 0;
    }
    for(i=0;i<MAX_TREE_SIZE;i++) {
        if (T[i] == e) { // �ҵ�e
            return T[i * 2 + 2];
        }
    }
    return 0; // û�ҵ�e
}

int LeftSibling(int* T,int e)
{ // ��ʼ������������T���ڣ�e��T��ĳ�����
    // �������������e�����ֵܡ���e��T�����ӻ������ֵܣ��򷵻أ��գ�
    int i;
    if(T[0]==0) { // ����
        return 0;
    }
    for(i=1;i<MAX_TREE_SIZE;i++) {
        if (T[i] == e && i % 2 == 0) { // �ҵ�e�������Ϊż��(���Һ���)
            return T[i - 1];
        }
    }
    return 0; // û�ҵ�e
}

int RightSibling(int* T,int e)
{ // ��ʼ������������T���ڣ�e��T��ĳ�����
    // �������������e�����ֵܡ���e��T���Һ��ӻ������ֵܣ��򷵻أ��գ�
    int i;
    if(T[0]==0) { // ����
        return 0;
    }
    for(i=1;i<=MAX_TREE_SIZE-1;i++) {
        if (T[i] == e && i % 2 != 0) { // �ҵ�e�������Ϊ����(������)
            return T[i + 1];
        }
    }
    return 0; // û�ҵ�e
}

void Move(int* q,int j,int* T,int i)
{ // �Ѵ�q��j��㿪ʼ��������Ϊ��T��i��㿪ʼ������
    if(q[2*j+1]!=0) { // q������������
        Move(q, (2 * j + 1), T, (2 * i + 1)); // ��q��j������������ΪT��i����������
    }
    if(q[2*j+2]!=0){ // q������������
        Move(q,(2*j+2),T,(2*i+2)); // ��q��j������������ΪT��i����������
    }
    T[i]=q[j]; // ��q��j�����ΪT��i���
    q[j]=0; // ��q��j����ÿ�
}


void InsertChild(int* T,int p,int LR,int* c)
{ // ��ʼ������������T���ڣ�p��T��ĳ������ֵ��LRΪ0��1����������ӻ����Һ��ӣ��ǿն�����c��T���ཻ��������Ϊ��
    // �������: ����LRΪ0��1,����cΪT��p���������������p����ԭ��������������Ϊc��������
    int j,k,i=0;
    for(j=0;j<(int)(pow(2,Depth(T)))-1;j++) { // ����p�����
        if (T[j] == p) // jΪp�����
            break;
    }
    k=2*j+1+LR; // kΪp������Һ��ӵ����
    if(T[k]!=0) { // pԭ��������Һ��Ӳ���
        Move(T, k, T, 2 * k + 2);
    }// �Ѵ�T��k��㿪ʼ��������Ϊ��k������������ʼ������
    Move(c,i,T,k); // �Ѵ�c��i��㿪ʼ��������Ϊ��T��k��㿪ʼ������
}
