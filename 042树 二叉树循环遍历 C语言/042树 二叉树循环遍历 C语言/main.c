#include "binarytree.h"
/*
 *  数据结构 二叉树树的循环遍历
 *  运行环境 Arch Linux (Manjaro Linux 18.04)KDE
 *  编译器 LLVM Clang 8.0
 *  请不要尝试在其他编译器中运行
 *  作者水平有限 bug在所难免 如有错误 欢迎指正
 *  qq 582521582
 *  QQ群 322085520
 * */
int main(void)
{
	int arr[] = { 6, 8, 9, 2, 4, 3, 1, 5 ,7};//准备数据
	/* 树创建后图示 这里使用平衡树的方式创建(不旋转)
	 *
	             6
			2		 8
	     1    4   7    9
	        3   5
	*/
	BinaryTree*  bitree = (BinaryTree*)malloc(sizeof(BinaryTree));
	assert(bitree != NULL);
	init_tree(bitree);
	for (int i = 0; i < len(arr); i++)
	{
		create_tree(bitree, arr[i]);//按照不旋转的二叉平衡搜索树的方式插入
	}
	printf("递归遍先序遍历二叉树\n");
	prevOrder(bitree->root);
	printf("\n循环先序遍历二叉树\n");
	prevor(bitree->root);

    printf("\n\n递归遍中序比那里二叉树\n");
    inOrder(bitree->root);
    printf("\n循环中序遍历二叉树\n");
    inor(bitree->root);

    printf("\n\n递归遍后序比那里二叉树\n");
    postOrder(bitree->root);
    printf("\n循环后序遍历二叉树\n");
    postor(bitree->root);

    printf("\n销毁二叉树...");
    clearBiTree(bitree->root);
    free(bitree);
    printf("\n销毁成功");
    printf("\n程序结束!\n按任意键退出...");
	getchar();
	return 0;
}
