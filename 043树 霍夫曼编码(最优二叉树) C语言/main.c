//赫夫曼树
#include "huffmantree.h"
int main(void) {
    /*
     *
     * 设某电报密文出现频率(*100后)为 5 29 7 8 14 23 3 11
     * 则构建出来的二叉树的WPL= 5*4+3*4+11*3+23*2+7*4+8*4+14*3+29*2 = 271
     * 图示建立后的其中之一的最优二叉树(Huffman树)为
     *                 100
     *           42           58
     *       23     19     29    29
     *            11   8       14  15
     *                5  3        7  8
     * 教材使用的严蔚敏的书 所以我们用数组来描述一颗Huffman树
     * 开始数密文是8个 所以叶子节点是8 生成的节点数一共是2n-1
     * 所以我们可以动态分配内存大小为2n-1
     * 我们将信息保存在如下结构体数组中
     *0   weight  parent  lchild  rchild    数组中0下标被弃用
     *1     *5     9                        parent记录的下标的位置
     *2     *29    14                       叶子节点没有左右孩子 所以默认用0代替
     *3     *7     10                       0刚好是被弃用的
     *4     *8     10
     *5     *14    29
     *6     *23    13
     *7     *3     9
     *8     *11    11                        初始化的位置到这里结束
     *9     *8     11       1       7        之后就是找到数组中权重最小的2个相加放下面
    *10     *15    29       3       4
    *11     *19    13       8       9
    *12     *29    14       5       10
    *13     *42    15       6       11
    *14     *58    15       2       12
    *15     100    0        13      14       生成的最后一个节点是根节点 没有父节点 用0代替
     *                                       因为0是在数组中被弃用的一个存储空间
     *
     * */
    //f=HT[i].parent;f!=0;f=HT[f].parent
    int w[8] = {
            5,29,7,8,14,23,3,11 //严蔚敏书上用例
    };
    HuffmanTree* HT = (HuffmanTree*)malloc((2*len(w)-1)*sizeof(HuffmanTree));//总结点个数
    memset(HT, 0, _msize(HT));
    HuffmanCode HC = (HuffmanCode)malloc((len(w))*sizeof(char*));
    HuffmanCoding(HT, HC, w, len(w));
    printf("霍夫曼对应的表\n");
    for (int i = 1; i <=len(w)*2-1; ++i) {
        printf("%d ",HT[i].weight);
    }
    printf("\n对应霍夫曼编码\n");
    for(int i = 1;i<=len(w);i++){
        printf("%s ", HC[i]);
    }
    return 0;
}