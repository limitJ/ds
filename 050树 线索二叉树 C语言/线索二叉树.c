#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct BiTNode
{
	char data;
	struct BiTNode* lchild, * rchild;
	int ltag;
	int rtag;/* 0表示指向左右孩子的指针
				1表示指向前驱后继的线索*/
} BiTNode, * BiTTree;

// 全局变量，始终指向刚刚访问过的结点
BiTTree pre;
//创建二叉树按照NULL为空格的方式输入数据
/*比如
			A
	      /   \
		 B     C
		   \
		    D
	就是 AB#D##C## 这里空格我用#代替
*/
void Create(BiTTree* T)//利用的是前序遍历
{
	char c;

	scanf("%c", &c);
	if (' ' == c)
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTNode*)malloc(sizeof(BiTNode));
		(*T)->data = c;
		(*T)->ltag = 0;//设置标志，常规的二叉树就没有这两个
		(*T)->rtag = 0;

		CreateBiTTree(&(*T)->lchild);
		CreateBiTTree(&(*T)->rchild);
	}
}
void InThreading(BiTTree T)//中序遍历给树设定线索
{
	if (T)
	{
		InThreading(T->lchild);		// 递归左孩子线索化

		if (!T->lchild)	// 如果该结点没有左孩子，设置左标志位为1，并把左孩子指向刚刚访问的结点
		{
			T->ltag = 1;
			T->lchild = pre;
		}

		if (!pre->rchild) //同理
		{
			pre->rtag = 1;
			pre->rchild = T;
		}

		pre = T;

		InThreading(T->rchild);		// 递归右孩子线索化
	}
}

void InOrderThreading(BiTTree* p, BiTTree T)
{
	*p = (BiTTree)malloc(sizeof(BiTNode));
	(*p)->ltag = 0;
	(*p)->rtag = 1;
	(*p)->rchild = *p;
	if (!T)
	{
		(*p)->lchild = *p;
	}
	else
	{
		(*p)->lchild = T;
		pre = *p;
		InThreading(T);
		pre->rchild = *p;
		pre->rtag = 1;
		(*p)->rchild = pre;
	}
}

void InOrderTraverse(BiTTree T)//中序遍历二叉树
{
	BiTTree p;
	p = T->lchild;

	while (p != T)
	{
		while (p->ltag == 0)
		{
			p = p->lchild;
		}
		printf("%c", p->data);

		while (p->rtag == 1 && p->rchild != T)
		{
			p = p->rchild;
			printf("%c", p->data);
		}

		p = p->rchild;
	}
}

int main()
{
	BiTTree P, T = NULL;
	Create(&T);
	InOrderThreading(&P, T);
	printf("中序遍历输出结果为: ");
	InOrderTraverse(P);
	printf("\n");
	return 0;
}