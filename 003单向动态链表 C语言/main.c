#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
/*
    数据结构: 动态链表存储
    by zhubin
    C标准:C99
    编译器版本: gcc (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
    IDE: CodeBlocks 17.01
    QQ: 582521582
    Q群:322085520
    字符编码: UTF-8
    平台: Windows 10 1809 专业版 64位

*/
typedef struct LinkedList
{
    int data;
    struct LinkedList* next;
}LinkList;
LinkList* create(int node_num);     //创建一个链表
void display(LinkList* linklist);   //显示链表数组
int len(LinkList* linkList);        //获取链表长度(不包含头结点)
bool isEmpty(LinkList* linkList);   //检查链表是否为空
bool insert(LinkList* linkList,int index); //在指定位置上插入数据
bool add(LinkList* linkList);              //在链表末尾添加数据
bool myremove(LinkList* linkList,int data); //移除链表中第一个出现指定数值的节点
int mydelete(LinkList* linkList,int index); //指定位置上删除节点
void sortLinklist(LinkList* linkList);      //对链表中的数据进行排序
int main(void)
{
    printf("请输入创建的链表长度\n");
    int node_num = 0;
    scanf("%d",&node_num);
    LinkList* linkList = create(node_num);
    display(linkList);
    printf("链表长度(不包含头结点): %d\n",len(linkList));
    if(isEmpty(linkList))
    {
        printf("是否为空: true\n");
    }
    else
    {
        printf("是否为空: false\n");
    }
    if(add(linkList))
    {
        printf("添加数据是否成功: true\n");
    }
    else
    {
        printf("添加数据是否成功: false\n");
    }
    display(linkList);
    printf("链表长度(不包含头结点): %d\n",len(linkList));
    int insert_index = 0;
    printf("请输入插入的位置:\n");
    scanf("%d",&insert_index);
    if(insert(linkList,insert_index))
    {
        printf("插入数据是否成功: true\n");
    }
    else
    {
        printf("插入数据是否成功: false\n");
    }
    display(linkList);
    printf("链表长度(不包含头结点): %d\n",len(linkList));
    int remove_data = 0;
    printf("请输入需要移除的数据:\n");
    scanf("%d",&remove_data);
    if(myremove(linkList,remove_data))
    {
        printf("移除数据是否成功: true\n");
    }
    else
    {
        printf("移除数据是否成功: false\n");
    }
    display(linkList);
    printf("链表长度(不包含头结点): %d\n",len(linkList));
    printf("请输入需要移除数据的位置:\n");
    int delete_index = 0;
    scanf("%d",&delete_index);
    printf("移除的数据是: %d\n",mydelete(linkList,delete_index));
    display(linkList);
    printf("链表长度(不包含头结点): %d\n",len(linkList));
    sortLinklist(linkList); //冒泡排序
    display(linkList);
    printf("链表长度(不包含头结点): %d\n",len(linkList));
    return 0;
}
LinkList* create(int node_num)
{
    LinkList* head = (LinkList*)malloc(sizeof(LinkList));
    if(head == NULL)
    {
        puts("分配起始内存失败!");
        exit(1);
    }
    LinkList* end = NULL;
    end = head;
    end->next = NULL;
    for(int i = 0; i<node_num;i++)
    {Release 17.12  rev 11256 (2017-12-28 10:44:41)   gcc 5.1.0 Windows/unicode - 32 bit
        LinkList* node = (LinkList*)malloc(sizeof(LinkList));
        if(node!=NULL)
        {
            printf("请输入第一个节点的数据:%d\n",i+1);
            int data = 0;
            scanf("%d",&data);
            node->data = data;
            end->next = node;
            end = node;
        }
        else
        {
            puts("分配节点内存失败");
            exit(1);
        }
    }
    end->next = NULL;
    return head;
}
void display(LinkList* linkList)
{
    if(len(linkList) == 0)
    {
        printf("LinkedList = []\n");
    }
    else
    {
       printf("LinkedList = [");
    }
    while((linkList = linkList->next)!=NULL)
    {
        if(linkList->next == NULL)
        {
            printf("%d]\n",linkList->data);
        }
        else
        {
            printf("%d,",linkList->data);
        }
    }
}
int len(LinkList* linkList)
{
    int len = 0;
    while((linkList = linkList->next)!=NULL)
    {
        ++len;
    }
    return len;
}
bool isEmpty(LinkList* linkList)
{
    if(len(linkList) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool add(LinkList* linkList)
{
    while(linkList->next!=NULL)
    {
        linkList = linkList->next;
    }
    LinkList* node = (LinkList*)malloc(sizeof(LinkList));
    if(node == NULL)
    {
        puts("分配节点内存失败,添加数据失败\n");
        return false;
    }
    else
    {
        linkList->next = node;
        node->next = NULL;
        int data = 0;
        printf("请输入要添加的数据: ");
        scanf("%d",&data);
        node->data = data;
        return true;
    }
}
bool insert(LinkList* linkList,int index)
{
    if(index > len(linkList)-1)
    {
        puts("数组越界,程序终止\n");
        exit(1);
    }
    for(int i = 0; i<index;i++)
    {
        linkList = linkList->next;
    }
    LinkList* node = (LinkList*)malloc(sizeof(LinkList));
    if(node == NULL)
    {
        puts("分配节点内存失败,添加数据失败\n");
        return false;
    }
    else
    {
        node->next = linkList->next;
        linkList->next = node;
        int data = 0;
        printf("请输入要添加的数据: ");
        scanf("%d",&data);
        node->data = data;
        return true;
    }
}
bool myremove(LinkList* linkList,int data)
{
    if(linkList == NULL)
    {
        puts("链表为空\n");
        return false;
    }
    while(linkList->next->data != data)
    {
        if(linkList->next->next == NULL)
        {
            return false;
        }
        linkList = linkList->next;
    }
    LinkList* temp = linkList->next;
    linkList->next = linkList->next->next;
    free(temp);
    return true;
}
int mydelete(LinkList* linkList,int index)
{
    if(index>len(linkList)-1 || index<0)
    {
        puts("数组越界,程序终止\n");
        exit(1);
    }
    for(int i = 0;i<index;i++)
    {
        linkList = linkList->next;
    }
    LinkList* temp = linkList->next;
    linkList->next = linkList->next->next;
    int data = temp->data;
    free(temp);
    return data;
}
void sortLinklist(LinkList* linkList)
{
    linkList = linkList->next;
    for(LinkList* node = linkList;node->next!=NULL;node = node->next)
    {
        for(LinkList* move = linkList;move->next!=NULL;move = move->next)
        {
            if(move->data > move->next->data)
            {
                int temp = move->data;
                move->data = move->next->data;
                move->next->data = temp;
            }
        }
    }
}
