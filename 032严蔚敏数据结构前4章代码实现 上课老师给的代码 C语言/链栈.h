 /* 链栈的基本操作(9个) */
 /* 大部分基本操作是由单链表.h中的函数改名得来 */
 
 typedef SElemType ElemType; /* 栈结点类型和链表结点类型一致 */
 typedef LinkList LinkStack; /* LinkStack是指向栈结点的指针类型 */
 #define InitStack InitList /* InitStack()与InitList()作用相同，下同 */
 #define DestroyStack DestroyList
 #define ClearStack ClearList
 #define StackEmpty ListEmpty
 #define StackLength ListLength
 #include"单链表.h"

 Status GetFirstElem(LinkStack S,ElemType *e)
 { /* 返回表头元素的值 */
   LinkStack p=S->next;
   if(!p) /* 空表 */
     return ERROR;
   else /* 非空表 */
     *e=p->data;
   return OK;
 }
 
 Status Push(LinkStack S,ElemType e)
 { /* 初始条件：栈S已存在。操作结果：在S的头部插入新的数据元素e,作为栈顶元素 */
   LinkStack p;
   p=(LinkStack)malloc(sizeof(struct LNode)); /* 生成新结点 */
   p->data=e; /* 给结点赋值 */
   p->next=S->next; /* 插在表头 */
   S->next=p;
   return OK;
 }
  
 Status Pop(LinkStack S,ElemType *e)
 { /* 初始条件：栈S已存在，且有不少于1个元素 */
   /* 操作结果：删除S的第一个数据元素，并由e返回其值 */
   LinkStack p=S->next;
   if(p)
   {
     *e=p->data;
     S->next=p->next;
     free(p);
     return OK;
   }
   else
     return ERROR;
 }
 
 Status StackTraverse(LinkStack S,void(*visit)(SElemType))
 { /* 从栈底到栈顶依次对栈中每个元素调用函数visit()。 */
   SElemType e;
   LinkStack temp,p=S;
   InitStack(&temp); /* 初始化temp栈 */
   while(p->next)
   {
     GetTop(p,&e);
     Push(temp,e);
     p=p->next;
   }
   ListTraverse(temp,visit);
   return OK;
 }