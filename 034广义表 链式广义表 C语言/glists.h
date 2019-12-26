//
// Created by zhubin on 2019/4/14.
// π„“Â±Ì
//

#ifndef C_GLISTS_H
#define C_GLISTS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define new(Object) (Object*)malloc(sizeof(Object))
enum tag {
	atom, list
};
typedef struct GLNode {
	int tag;
	union {
		char atom;
		struct GLNode* head;
	};
	struct GLNode* tail;
}GList, GNode;
GList* create(char* str,int* index);
void output(GList* head);
int Depth(GList* head);
int Length(GList* head);
GList* Copy(GList* head);
#endif //C_GLISTS_H
