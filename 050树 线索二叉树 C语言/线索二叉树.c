#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct BiTNode
{
	char data;
	struct BiTNode* lchild, * rchild;
	int ltag;
	int rtag;/* 0��ʾָ�����Һ��ӵ�ָ��
				1��ʾָ��ǰ����̵�����*/
} BiTNode, * BiTTree;

// ȫ�ֱ�����ʼ��ָ��ոշ��ʹ��Ľ��
BiTTree pre;
//��������������NULLΪ�ո�ķ�ʽ��������
/*����
			A
	      /   \
		 B     C
		   \
		    D
	���� AB#D##C## ����ո�����#����
*/
void Create(BiTTree* T)//���õ���ǰ�����
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
		(*T)->ltag = 0;//���ñ�־������Ķ�������û��������
		(*T)->rtag = 0;

		CreateBiTTree(&(*T)->lchild);
		CreateBiTTree(&(*T)->rchild);
	}
}
void InThreading(BiTTree T)//������������趨����
{
	if (T)
	{
		InThreading(T->lchild);		// �ݹ�����������

		if (!T->lchild)	// ����ý��û�����ӣ��������־λΪ1����������ָ��ոշ��ʵĽ��
		{
			T->ltag = 1;
			T->lchild = pre;
		}

		if (!pre->rchild) //ͬ��
		{
			pre->rtag = 1;
			pre->rchild = T;
		}

		pre = T;

		InThreading(T->rchild);		// �ݹ��Һ���������
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

void InOrderTraverse(BiTTree T)//�������������
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
	printf("�������������Ϊ: ");
	InOrderTraverse(P);
	printf("\n");
	return 0;
}