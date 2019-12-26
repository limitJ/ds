#include <stdio.h>
#include <stdlib.h>
int i = 0;
int IsFirst = 1;//�ж��Ƿ�Ϊ��һ�㣬Ϊ��һ�㣨���ǵ�һ���ڵ㣩
typedef struct Node
{
	int data;
	struct Node* lchild,* rchild;
}BinarySortTree;//��
void Binary_Sort_Tree(int *array, BinarySortTree **p)//��������������
{
	while (i < 8)//��Ϊ��������9��Ԫ��
	{
		leap:
		BinarySortTree* newNode;
		if (array[i + 1] > (*p)->data && (*p)->rchild != NULL && i != 8)//����������������һ�����Ƚϴ��ڣ����ҵ�һ���ڵ����������Ϊ�գ��Ǿ͵ݹ����������
		{
			IsFirst++;
			Binary_Sort_Tree(array, &(*p)->rchild);
			if (IsFirst != 1)//�����Ϊ��һ��ͷ��أ���㷵��
			{
				IsFirst--;
				return;
			}
			goto leap;//�ݹ���������¿�ʼ�ж�
		}
		else if (array[i + 1] < (*p)->data && (*p)->lchild != NULL && i != 8)//����������������һ�����Ƚ�С�ڣ����ҵ�һ���ڵ����������Ϊ�գ��Ǿ͵ݹ����������
		{
			IsFirst++;
			Binary_Sort_Tree(array, &(*p)->lchild);
			if (IsFirst != 1)//�����Ϊ��һ��ͷ��أ���㷵��
			{
				IsFirst--;
				return;
			}
			goto leap;//�ݹ���������¿�ʼ�ж�
		}
		if (array[i + 1] > (*p)->data && (*p)->rchild == NULL && (i + 1) != 9)//�������Ԫ�ش��ڵ�һ��Ԫ�ز���������Ϊ�գ���ôֱ�Ӹ�ֵ��������
		{
			newNode = (BinarySortTree*)malloc(sizeof(BinarySortTree));
			newNode->lchild = NULL;
			newNode->rchild = NULL;
			newNode->data = array[i + 1];
			(*p)->rchild = newNode;
			i++;
			if ((*p)->data != array[0])//������Ϊ�˵ݹ��з��أ��ų��˵�һ��Ԫ�ظ�ֵ�����
			{
				IsFirst--;//���Ϸ�����һ�����Լ���һ��
				return;
			}
		}
		else if (array[i + 1] < (*p)->data && (*p)->lchild == NULL && (i + 1) != 9)//�������Ԫ�ش��ڵ�һ��Ԫ�ز���������Ϊ�գ���ôֱ�Ӹ�ֵ��������
		{
			newNode = (BinarySortTree*)malloc(sizeof(BinarySortTree));
			newNode->lchild = NULL;
			newNode->rchild = NULL;
			newNode->data = array[i + 1];
			(*p)->lchild = newNode;
			i++;
			if ((*p)->data != array[0])
			{
				IsFirst--;
				return;
			}
		}
		
	}
}
int Search(BinarySortTree *T, int key, BinarySortTree *f, BinarySortTree **p)//����������
{
	if (T == NULL)
	{
		*p = f;
		return 0;
	}
	else if (key == T->data)
	{
		*p = T;
		return 1;
	}
	else if (key < T->data)
	{
		return Search(T->lchild, key, T, p);
	}
	else
	{
		return Search(T->rchild, key, T, p);
	}
}
int InsertBST(BinarySortTree** T, int key)//�����������Ĳ���
{
	BinarySortTree* p,* s;
	if (Search(*T, key, NULL, &p) == 0)
	{
		s = (BinarySortTree*)malloc(sizeof(BinarySortTree));
		s->data = key;
		s->lchild = NULL;
		s->rchild = NULL;
		if (p == NULL)//p�����NULLֵ˵�������Ϊ��ֱ�Ӳ���Ϊͷ�ڵ�
		{
			*T = s;
		}
		else if (key < p->data)
		{
			p->lchild = s;
		}
		else
		{
			p->rchild = s;
		}
		return 1;
	}
	else
	{
		return 0;
	}
}
void InOrder(BinarySortTree* T)//�������������
{
	if (T != NULL)
	{
		InOrder(T->lchild);
		printf("%d ", T->data);
		InOrder(T->rchild);
	}
}
int Delete(BinarySortTree** T)
{
	BinarySortTree* p, * s;//��ʱ�ڵ�
	if ((*T)->rchild == NULL)//���Ҫɾ���Ľڵ�������Ϊ��ֱ�ӽ�����ڵ��ֵ���������������
	{
		p = *T;
		*T = (*T)->lchild;
		free(p);
	}
	else if ((*T)->lchild == NULL)//ͬ��
	{
		p = *T;
		*T = (*T)->rchild;
		free(p);
	}
	else/*�������������������ڵ�ʱ��,��ʱ��Ҫ�ҵ�Ҫɾ���ڵ��ֱ��ǰ������ֱ�Ӻ��
		  ����ڵ�������������ҵĽڵ����ǰ��Ԫ�أ���Ϊ�ڵ������������ҵ�Ԫ������������������Ԫ��
		*/
	{
		p = *T;
		s = (*T)->lchild;
		while (s->rchild)
		{
			p = s;
			s = s->rchild;
		}
		(*T)->data = s->data;
		if (p != *T)
		{
			p->rchild = s->lchild;
		}
		else
		{
			p->lchild = s->lchild;
		}
		free(s);
	}
	return 1;
}
int DeleteBST(BinarySortTree** T, int key)//Ѱ��Ҫɾ���Ľڵ�
{
	if ((*T) == NULL)
	{
		return 0;
	}
	else
	{
		if (key == (*T)->data)
		{
			return Delete(T);
		}
		else if (key < (*T)->data)
		{
			return DeleteBST(&(*T)->lchild, key);
		}
		else
		{
			return DeleteBST(&(*T)->rchild, key);
		}
	}
}

/*
                  105
               /       \
              70       115
			 /  \      /
			67	104   111
           /    /      /
		  46    99    109

*/
int main(void)
{
	BinarySortTree* p = (BinarySortTree*)malloc(sizeof(BinarySortTree));
	p->lchild = NULL;
	p->rchild = NULL;
	int array[] = {70, 105, 115, 104, 67, 46, 99, 111, 109 };
	p->data = array[i];//�Ƚ�����ĵ�һ��ֵ�������ĵ�һ���ڵ�
	Binary_Sort_Tree(array, &p);
	printf("ɾ��ǰ:\n");
	InsertBST(&p, 100);
	InOrder(p);
	printf("\n");
	printf("ɾ����:\n");
	DeleteBST(&p, 70);
	InOrder(p);
}