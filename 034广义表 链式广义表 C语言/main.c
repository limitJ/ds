#include "glists.h"
#include <string.h>
/*
*	数据结构 广义表
*   类似python中的列表
*	编译器 Visaul Stdio 2019
*	
*/
int main(void) {
	char* str= "(1,(5,2,3),5,6,8)";
	int index = 0;
	GList* head = create(str,&index);
	output(head);
	printf("%d %d", Depth(head), Length(head));
	GList* h = Copy(head);
	output(h);
	return 0;
}