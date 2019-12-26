/*
 * 课程： 操作系统原理
 * 程序： 首次适应内存分配算法
 * 学号： 1817249038
 * 教师： 苏州大学 王辉
 * 编译器： LLVM clang v8.0 c11 / gcc v8.3.0 c11
 * 运行平台: manjaro linux dde v18.02
 * 编辑器： neovim v0.4
 * 日期: 2019-06-09 22:28
 * */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <memory.h>

#define throwException(e) fputs(e,stderr)

typedef unsigned int uint;

typedef struct tag_mem_block {
    int pid;//进程的Pid
    uint start_address;//进程的起始地址
    uint size;//进程的大小
    struct tag_mem_block* next;//链表 指向的下一个节点
}MemBlock ;

char memory_image[4096];//位镜像 稍做改动 不乘以1024 方便计算

MemBlock* list = NULL;//头指针
MemBlock* tail = NULL;//自添加部分 本程序链表使用尾插法 需要维护尾指针

MemBlock* getMemBlock(int pid,uint mem_size){
    if (mem_size > 4096) {
        throwException("分配失败，空间不足\n");
        return NULL;
    }
    if (mem_size%4 != 0) {
        throwException("错误，分配内存必须是4KB的倍数\n");
        return NULL;
    }
    if(mem_size <= 0){
        throwException("错误,分配内存至少4KB起步\n");
        return NULL;
    }
    if(list == NULL){
        //说明程序是第一次分配
        list = (MemBlock*)malloc(sizeof(MemBlock));
        if(list == NULL){
            throwException("系统分配失败！\n");
            return NULL;
        }
        list->start_address = 0;
        list->pid = pid;
        list->size = mem_size;
        list->next = NULL;
        tail = list;
        return list;
    }else{
        //找到一块空闲块 并且足够分配的区域
        MemBlock* new_MemBlock = (MemBlock*)malloc(sizeof(MemBlock));
        if (new_MemBlock == NULL) {
            throwException("系统分配失败！\n");
            return NULL;
        }
        MemBlock* temp = list;
        for (MemBlock* old = list;old!=NULL;old = old->next) {
            if (old->pid == pid) {
                printf("进程%d已存在，分配失败\n",pid);
		free(new_MemBlock);
                return NULL;
            }
        }
        //存在空闲 但空闲在head 也就是list节点之前 如果有空闲就分配空间
        if (list->start_address!=0 && list->start_address >= mem_size) {
            new_MemBlock->next = list;
            new_MemBlock->pid = pid;
            new_MemBlock->size = mem_size;
            new_MemBlock->start_address = 0;
            list = new_MemBlock;
            return list;
        }
        //往后面找空闲
        while(temp!=NULL){
            if(temp->next != NULL){
                //说明该节点是空闲的 且节点后面有挂着的节点 则在中间找空闲
                if(temp->next->start_address - (temp->start_address + temp->size) >= mem_size){
                    //说明还有空间可以分配
                    new_MemBlock->next = temp->next;
                    new_MemBlock->size = mem_size;
                    new_MemBlock->pid = pid;
                    new_MemBlock->start_address = temp->start_address+temp->size;
                    temp->next = new_MemBlock;
                    return new_MemBlock;
                }else{
                    //继续寻找
                    temp = temp->next;
                }
            }else if(temp->next==NULL){
                //找到空闲 并且是在尾节点挂上一个空间 需要修改尾节点
                if(temp->start_address + temp->size + mem_size >4096){
                    throwException("分配失败，空间不足\n");
                    return NULL;
                }
                new_MemBlock->next = NULL;
                new_MemBlock->pid = pid;
                new_MemBlock->start_address = tail->start_address+tail->size;
                new_MemBlock->size = mem_size;
                tail->next = new_MemBlock;
                tail =  new_MemBlock;
                return new_MemBlock;
            }
        }
    }
    return NULL;
}

bool freeMemblock(MemBlock* mb){
    if (mb == NULL || list == NULL) {
        throwException("空指针，释放失败\n");
        return false;
    }
    MemBlock* temp = list;
    //释放空间 如果该空间就是头节点
    if(list == mb){
        list = list->next;
        if(list == NULL){//说明只存在一个节点了
            tail = NULL;
        }
        free(mb);
        return true;
    }else{
        //否则找到待释放节点的的前一个节点
        while(temp->next!=mb){
            temp = temp->next;
        }
        //令待释放节点的前一个节点指向待释放节点的下一个节点
        temp->next = mb->next;
        //如果待释放节点的下一个节点是空 则要修改尾节点的指向
        if (temp->next == NULL) {
            tail = temp;
        }
        free(mb);
        return true;
    }
}

void showMemImage(){
    //一行64个字符 *代表占用4KB -代表空闲4KB 每个4KB 一行256KB
    //一共4096KB 共16行数据
    memset(memory_image, '-', sizeof(memory_image));
    for (MemBlock* temp = list; temp!=NULL; temp = temp->next) {
        for (int i = temp->start_address;i < temp->start_address+temp->size; i++) {
            memory_image[i] = '*';
        }
    }
    for (int i = 0; i < 4096; i+=4) {
        if (i%256 == 0) {
            printf("\n");
        }
        printf("%c",memory_image[i]);
    }
    printf("\n");
}

int main(void)
{
    printf("++++++++++++++++++++++++++++++\n");
    printf("++++++++++请选择功能++++++++++\n");
    printf("++++++++++1:申请内存++++++++++\n");
    printf("++++++++++2:释放内存++++++++++\n");
    printf("++++++++++3:内存图示++++++++++\n");
    printf("++++++++++4:内存描述++++++++++\n");
    printf("++++++++++c:按c清屏+++++++++++\n");
    printf("++++++++++q:按q退出+++++++++++\n");
    printf("++++++++++++++++++++++++++++++\n");
    printf("请选择功能: ");
    char ch;
    int pid = 0;
    uint mem_size = 0;
    while((ch = getchar())!='q'){
        switch (ch) {
            case '1':
                printf("输入pid号和容量内存(4-4096KB 4的倍数) 输入用空格隔开\n");
                scanf("%d%d",&pid,&mem_size); // NOLINT(cert-err34-c)
                if(getMemBlock(pid, mem_size) == NULL){
                    printf("进程%d申请失败\n",pid);
                }else{
                    printf("进程%d申请成功\n",pid);
                }
                break;
            case '2':
                printf("请输入需要kill的进程pid号\n");
                scanf("%d",&pid); // NOLINT(cert-err34-c)
                bool flag = false;
                for (MemBlock* temp = list;temp!=NULL;temp=temp->next) {
                    if (temp->pid == pid) {
                        flag = freeMemblock(temp);
                    }
                }
                if(flag == false){
                    printf("进程:%d 释放失败\n",pid);
                }else{
                    printf("进程:%d 释放成功\n",pid);
                }
                break;
            case '3':
                showMemImage();
                break;
            case '4':
                for (MemBlock* temp=list;temp!=NULL;temp=temp->next) {
                    printf("进程:%d 起址:%d 大小:%dKB\n",temp->pid,temp->start_address,temp->size);
                }
                if (list == NULL) {
                    printf("进程:无 起址:0 大小:0KB\n");
                }
                break;
            case 'c':
                #ifdef _WIN32
                system("cls");
                #else
                system("clear");
                #endif
                printf("++++++++++++++++++++++++++++++\n");
                printf("++++++++++请选择功能++++++++++\n");
                printf("++++++++++1:申请内存++++++++++\n");
                printf("++++++++++2:释放内存++++++++++\n");
                printf("++++++++++3:内存图示++++++++++\n");
                printf("++++++++++4:内存描述++++++++++\n");
                printf("++++++++++c:按c清屏+++++++++++\n");
                printf("++++++++++q:按q退出+++++++++++\n");
                printf("++++++++++++++++++++++++++++++\n");
                break;
            default:
                continue;
        }
        printf("\n请选择功能: ");
    }

    //程序结束 销毁已分配内存
    for (;list!=NULL;list=list->next) {
        free(list);
    }
    printf("程序结束!\n");

    return 0;
}
