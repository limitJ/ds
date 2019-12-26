#include "binarytree.h"
int main(void)
{
    int arr1[] = {
            0,1,2,3,4,5,6,7,8,9
    };
    int arr2[] = {
            10,11,12,13,14,15,16,17,18,19
    };
    BinaryTree *bit1 = (BinaryTree *) malloc(sizeof(BinaryTree));
    BinaryTree *bit2 = (BinaryTree *) malloc(sizeof(BinaryTree));
    init_bitree(bit1, NULL);
    init_bitree(bit2, NULL);
    bitree_ins_left(bit1,NULL,&arr1[0]);
    bitree_ins_left(bit2, NULL, &arr2[0]);
    bitree_ins_left(bit1,bit1->root,&arr1[1]);
    bitree_ins_right(bit1, bit1->root, &arr1[2]);
    bitree_ins_left(bit2,bit2->root,&arr2[1]);
    bitree_ins_right(bit2, bit2->root, &arr2[2]);
    printf("%d\n", *(int*)bit1->root->data);
    printf("%d\n", *(int*)bit2->root->data);
    BinaryTree* merge = (BinaryTree *) malloc(sizeof(BinaryTree));
    int element = 233;
    bitree_merge(merge, bit1, bit2, &element);
    printf("%d\n", *(int*)merge->root->data);
    printf("%d\n", *(int*)merge->root->left->data);
    printf("%d\n", *(int*)merge->root->right->data);
    printf("dep = %d\n", depth(merge->root));
    return 0;
}