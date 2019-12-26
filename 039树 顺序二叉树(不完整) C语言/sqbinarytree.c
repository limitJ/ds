//
// Created by qq 582521582 on 2019/4/22.
//
#include "sqbinarytree.h"
void InitBiTree(int* T){ // 构造空二叉树T。因为T是数组名
    //pass 为了方便 main函数直接用样例数据了 就不需要初始化了
    printf("初始化成功！");
}

void CreateBiTree(int* T){

    for(int i=1;i<MAX_TREE_SIZE;i++)
        if(T[(i+1)/2-1]==0&&T[i]!=0) // 此结点(不空)无双亲且不是根
        {
           printf("出现无双亲的非根结点%d\n",T[i]);
           exit(-1);
        }
}

bool isEmpty(int* T){ // 初始条件：二叉树T存在。操作结果：若T为空二叉树，则返回TRUE，否则FALSE
    return 0 == T[0];//很简单 根节点为空 则二叉树肯定为空
}

int Depth(int* T){ // 初始条件：二叉树T存在。操作结果：返回T的深度
    int i,j=-1;
    for(i=MAX_TREE_SIZE-1;i>=0;i--) { // 找到最后一个结点
        if (T[i] != 0) {
            break;
        }
    }
    i++;
    do {
        j++;
    }while(i>=pow(2,j)); //就是看在第几层 第i层的数在T中的下表范围是2^(i-1) - 1 ~ 2^i - 2之间
    return j;
}

int Root(int* T){ // 初始条件：二叉树T存在。操作结果：当T不空，
    if(isEmpty(T)) { // T空
        return -1;
    }
    return T[0];
}

int Value(int* T,Pos e)
{ // 初始条件：二叉树T存在，e是T中某个结点(的位置)
    // 操作结果：返回处于位置e(层,本层序号)的结点的值
    return T[(int)(pow(2,e.level-1)+e.order-2)];
}

bool Assign(int* T,Pos e,int value)
{ // 初始条件：二叉树T存在，e是T中某个结点(的位置)
    // 操作结果：给处于位置e(层,本层序号)的结点赋新值value
    int i=(int)(pow(2,e.level-1)+e.order-2); // 将层、本层序号转为矩阵的序号
    if(value!=0&&T[(i+1)/2-1]==0) { // 给叶子赋非空值但双亲为空
        return false;
    }else if(value==0&&(T[i*2+1]!=0||T[i*2+2]!=0)) { //  给双亲赋空值但有叶子(不空)
        return false;
    }
    T[i]=value;
    return true;
}

int Parent(int* T,int e)
{ // 初始条件：二叉树T存在，e是T中某个结点
    // 操作结果：若e是T的非根结点，则返回它的双亲，否则返回＂空0＂
    int i;
    if(T[0]==0) { // 空树
        return 0;
    }
    for(i=1;i<MAX_TREE_SIZE;i++) {
        if (T[i] == e) { // 找到e
            return T[(i + 1) / 2 - 1];
        }
    }
    return 0; // 没找到e
}

int LeftChild(int* T,int e)
{ // 初始条件：二叉树T存在，e是T中某个结点。操作结果：返回e的左孩子。若e无左孩子,则返回"空"
    int i;
    if(T[0]==0) { // 空树
        return 0;
    }
    for(i=0;i<MAX_TREE_SIZE;i++) {
        if (T[i] == e) { // 找到e
            return T[i * 2 + 1];
        }
    }
    return 0; // 没找到e
}

int RightChild(int* T,int e)
{ // 初始条件：二叉树T存在，e是T中某个结点。操作结果：返回e的右孩子。若e无右孩子,则返回"空"
    int i;
    if(T[0]==0) { // 空树
        return 0;
    }
    for(i=0;i<MAX_TREE_SIZE;i++) {
        if (T[i] == e) { // 找到e
            return T[i * 2 + 2];
        }
    }
    return 0; // 没找到e
}

int LeftSibling(int* T,int e)
{ // 初始条件：二叉树T存在，e是T中某个结点
    // 操作结果：返回e的左兄弟。若e是T的左孩子或无左兄弟，则返回＂空＂
    int i;
    if(T[0]==0) { // 空树
        return 0;
    }
    for(i=1;i<MAX_TREE_SIZE;i++) {
        if (T[i] == e && i % 2 == 0) { // 找到e且其序号为偶数(是右孩子)
            return T[i - 1];
        }
    }
    return 0; // 没找到e
}

int RightSibling(int* T,int e)
{ // 初始条件：二叉树T存在，e是T中某个结点
    // 操作结果：返回e的右兄弟。若e是T的右孩子或无右兄弟，则返回＂空＂
    int i;
    if(T[0]==0) { // 空树
        return 0;
    }
    for(i=1;i<=MAX_TREE_SIZE-1;i++) {
        if (T[i] == e && i % 2 != 0) { // 找到e且其序号为奇数(是左孩子)
            return T[i + 1];
        }
    }
    return 0; // 没找到e
}

void Move(int* q,int j,int* T,int i)
{ // 把从q的j结点开始的子树移为从T的i结点开始的子树
    if(q[2*j+1]!=0) { // q的左子树不空
        Move(q, (2 * j + 1), T, (2 * i + 1)); // 把q的j结点的左子树移为T的i结点的左子树
    }
    if(q[2*j+2]!=0){ // q的右子树不空
        Move(q,(2*j+2),T,(2*i+2)); // 把q的j结点的右子树移为T的i结点的右子树
    }
    T[i]=q[j]; // 把q的j结点移为T的i结点
    q[j]=0; // 把q的j结点置空
}


void InsertChild(int* T,int p,int LR,int* c)
{ // 初始条件：二叉树T存在，p是T中某个结点的值，LR为0或1代表插入左孩子还是右孩子，非空二叉树c与T不相交且右子树为空
    // 操作结果: 根据LR为0或1,插入c为T中p结点的左或右子树。p结点的原有左或右子树则成为c的右子树
    int j,k,i=0;
    for(j=0;j<(int)(pow(2,Depth(T)))-1;j++) { // 查找p的序号
        if (T[j] == p) // j为p的序号
            break;
    }
    k=2*j+1+LR; // k为p的左或右孩子的序号
    if(T[k]!=0) { // p原来的左或右孩子不空
        Move(T, k, T, 2 * k + 2);
    }// 把从T的k结点开始的子树移为从k结点的右子树开始的子树
    Move(c,i,T,k); // 把从c的i结点开始的子树移为从T的k结点开始的子树
}
