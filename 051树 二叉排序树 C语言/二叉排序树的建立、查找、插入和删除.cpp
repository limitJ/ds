#include <stdio.h>
#include <stdlib.h>
int i = 0;
int IsFirst = 1;//判断是否为第一层，为第一层（就是第一个节点）
typedef struct Node
{
	int data;
	struct Node* lchild,* rchild;
}BinarySortTree;//树
void Binary_Sort_Tree(int *array, BinarySortTree **p)//创建二叉排序树
{
	while (i < 8)//因为我数组有9个元素
	{
		leap:
		BinarySortTree* newNode;
		if (array[i + 1] > (*p)->data && (*p)->rchild != NULL && i != 8)//如果数组后面的数与第一个数比较大于，并且第一个节点的右子树不为空，那就递归进入右子树
		{
			IsFirst++;
			Binary_Sort_Tree(array, &(*p)->rchild);
			if (IsFirst != 1)//如果不为第一层就返回，逐层返回
			{
				IsFirst--;
				return;
			}
			goto leap;//递归结束后重新开始判断
		}
		else if (array[i + 1] < (*p)->data && (*p)->lchild != NULL && i != 8)//如果数组后面的数与第一个数比较小于，并且第一个节点的左子树不为空，那就递归进入左子树
		{
			IsFirst++;
			Binary_Sort_Tree(array, &(*p)->lchild);
			if (IsFirst != 1)//如果不为第一层就返回，逐层返回
			{
				IsFirst--;
				return;
			}
			goto leap;//递归结束后重新开始判断
		}
		if (array[i + 1] > (*p)->data && (*p)->rchild == NULL && (i + 1) != 9)//如果数组元素大于第一个元素并且右子树为空，那么直接赋值，并连接
		{
			newNode = (BinarySortTree*)malloc(sizeof(BinarySortTree));
			newNode->lchild = NULL;
			newNode->rchild = NULL;
			newNode->data = array[i + 1];
			(*p)->rchild = newNode;
			i++;
			if ((*p)->data != array[0])//这里是为了递归有返回，排除了第一个元素赋值的情况
			{
				IsFirst--;//马上返回上一层所以减少一层
				return;
			}
		}
		else if (array[i + 1] < (*p)->data && (*p)->lchild == NULL && (i + 1) != 9)//如果数组元素大于第一个元素并且左子树为空，那么直接赋值，并连接
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
int Search(BinarySortTree *T, int key, BinarySortTree *f, BinarySortTree **p)//二叉树查找
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
int InsertBST(BinarySortTree** T, int key)//二叉排序树的插入
{
	BinarySortTree* p,* s;
	if (Search(*T, key, NULL, &p) == 0)
	{
		s = (BinarySortTree*)malloc(sizeof(BinarySortTree));
		s->data = key;
		s->lchild = NULL;
		s->rchild = NULL;
		if (p == NULL)//p如果是NULL值说明这颗树为空直接插入为头节点
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
void InOrder(BinarySortTree* T)//中序遍历二叉树
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
	BinarySortTree* p, * s;//临时节点
	if ((*T)->rchild == NULL)//如果要删除的节点右子树为空直接将这个节点的值用它的左子树替代
	{
		p = *T;
		*T = (*T)->lchild;
		free(p);
	}
	else if ((*T)->lchild == NULL)//同理
	{
		p = *T;
		*T = (*T)->rchild;
		free(p);
	}
	else/*左子树和右子树都存在的时候,此时就要找到要删除节点的直接前驱或者直接后继
		  比如节点的左子树的最右的节点就是前驱元素，因为节点左子树的最右的元素是整颗左子树最大的元素
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
int DeleteBST(BinarySortTree** T, int key)//寻找要删除的节点
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
	p->data = array[i];//先将数组的第一个值赋予树的第一个节点
	Binary_Sort_Tree(array, &p);
	printf("删除前:\n");
	InsertBST(&p, 100);
	InOrder(p);
	printf("\n");
	printf("删除后:\n");
	DeleteBST(&p, 70);
	InOrder(p);
}