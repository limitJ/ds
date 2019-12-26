 /* ��ջ�Ļ�������(9��) */
 /* �󲿷ֻ����������ɵ�����.h�еĺ����������� */
 
 typedef SElemType ElemType; /* ջ������ͺ�����������һ�� */
 typedef LinkList LinkStack; /* LinkStack��ָ��ջ����ָ������ */
 #define InitStack InitList /* InitStack()��InitList()������ͬ����ͬ */
 #define DestroyStack DestroyList
 #define ClearStack ClearList
 #define StackEmpty ListEmpty
 #define StackLength ListLength
 #include"������.h"

 Status GetFirstElem(LinkStack S,ElemType *e)
 { /* ���ر�ͷԪ�ص�ֵ */
   LinkStack p=S->next;
   if(!p) /* �ձ� */
     return ERROR;
   else /* �ǿձ� */
     *e=p->data;
   return OK;
 }
 
 Status Push(LinkStack S,ElemType e)
 { /* ��ʼ������ջS�Ѵ��ڡ������������S��ͷ�������µ�����Ԫ��e,��Ϊջ��Ԫ�� */
   LinkStack p;
   p=(LinkStack)malloc(sizeof(struct LNode)); /* �����½�� */
   p->data=e; /* ����㸳ֵ */
   p->next=S->next; /* ���ڱ�ͷ */
   S->next=p;
   return OK;
 }
  
 Status Pop(LinkStack S,ElemType *e)
 { /* ��ʼ������ջS�Ѵ��ڣ����в�����1��Ԫ�� */
   /* ���������ɾ��S�ĵ�һ������Ԫ�أ�����e������ֵ */
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
 { /* ��ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���visit()�� */
   SElemType e;
   LinkStack temp,p=S;
   InitStack(&temp); /* ��ʼ��tempջ */
   while(p->next)
   {
     GetTop(p,&e);
     Push(temp,e);
     p=p->next;
   }
   ListTraverse(temp,visit);
   return OK;
 }