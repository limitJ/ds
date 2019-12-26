#include "binarytree.h"
#include "stack.h"
/*
 *  数据结构 二叉树树的循环遍历
 *  运行环境 Arch Linux (Manjaro Linux 18.04)KDE
 *  编译器 LLVM Clang 8.0
 *  请不要尝试在其他编译器中运行
 *  qq 582521582
 *  QQ群 322085520
 * */
void init_tree(BinaryTree* bitree){
	bitree->root = NULL;
	bitree->size = 0;
}
void create_tree(BinaryTree* bitree, int data){
	
	if (bitree->root == NULL)
	{
		bitree->root = (Node*)malloc(sizeof(Node));
		assert(bitree->root != NULL);
		bitree->root->data = data;
		bitree->root->left = NULL;
		bitree->root->right = NULL;
	}
	else{
		Node* temp = bitree -> root;
		Node* newNode = (Node*)malloc(sizeof(Node));
		assert(newNode != NULL);
		newNode->data = data;
		newNode->left = NULL;
		newNode->right = NULL;
		while (temp!=NULL){
			if (newNode->data < temp->data){
				if (temp->left == NULL){
					temp->left = newNode;
					break;
				}
				else{
					temp = temp->left;
				}
			}
			else if (newNode->data >= temp->data){
				if (temp->right == NULL){
					temp->right = newNode;
					break;
				}
				else{
					temp = temp->right;
				}
			}
		}
	}
	bitree->size++;
}
void clearBiTree(Node* root){
    if (root != NULL){
        clearBiTree(root->left);
        clearBiTree(root->right);
        free(root);
    }
}
void prevOrder(Node* root){
    if (root != NULL){
        printf("%d ", root->data);
        prevOrder(root->left);
        prevOrder(root->right);
    }
}
void inOrder(Node* root){
    if (root != NULL){
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}
void postOrder(Node* root){
    if (root != NULL){
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

void inor(Node* root){
    Stack* stack = (Stack*)malloc(sizeof(stack));
    assert(stack!=NULL);
    initStack(stack);
    Node *p = root;
    while (p!=NULL || !isEmpty(stack)) {
        if (p->left!=NULL) {
            push(stack, p);
            p = p->left;
        } else{
            printf("%d ", p->data);
            p = p->right;
            while(!p && !isEmpty(stack)){
                p = peek(stack);
                printf("%d ",p->data);
                pop(stack);
                p = p->right;
            }
        }
    }
    clearStack(stack);
    free(stack);
    printf("\n");
}
void prevor(Node* root){
    Stack* stack = (Stack*)malloc(sizeof(stack));
    assert(stack!=NULL);
    initStack(stack);
    Node *p = root;
    while(p || !isEmpty(stack))
    {
        printf("%d ", p->data);
        push(stack,p);
        p = p->left;
        while(!p && !isEmpty(stack)){
            p = peek(stack);
            pop(stack);
            p = p->right;
        }
    }
    clearStack(stack);
    free(stack);
    printf("\n");
}
void postor(Node* root){
    Stack* stack = (Stack*)malloc(sizeof(stack));
    assert(stack!=NULL);
    initStack(stack);
    Node *p = root;
    Node* pre = NULL;
    push(stack,p);
    while(!isEmpty(stack)){
        p = peek(stack);
        if((p->left==NULL && p->right==NULL) || (pre!=NULL && (p->left==pre || p->right==pre)))
        {
            printf("%d ", p->data);
            pop(stack);
            pre = p;
        }else{
            if(p->right != NULL)
                push(stack,p->right);
            if(p->left != NULL)
                push(stack,p->left);
        }
    }
    clearStack(stack);
    free(stack);
    printf("\n");
}