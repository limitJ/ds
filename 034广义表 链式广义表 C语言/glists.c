#include "glists.h"
GList* create(char* str,int* index) {
	GNode* head = new(GNode);
	GNode* prev = NULL;
	prev = head;
	(*index)++;
	while (str[*index]) {
		if (str[*index] >= '0' && str[*index] <= '9') {
			prev->tag = atom;
			prev->atom = str[*index];
			prev->tail = new(GNode);
			prev = prev->tail;
			(*index)++;
		}
		else if (str[*index] == '(') {
			prev->tag = list;
			prev->head = create(str,index);
			prev->tail = new(GNode);
			prev = prev->tail;
			(*index)++;
		}
		else if (str[*index] == ')') {
			prev = NULL;
			return head;
		}
		else (*index)++;
	}
	return head;
}

void output(GList* head) {
	printf("(");
	GNode* prev = head;
	while (prev) {
		if (prev->tag == atom) {
			printf("%c", prev->atom);
			prev = prev->tail;
		}
		else if (prev->tag == list) {
			output(prev->head);
			prev = prev->tail;
		}
		if (prev->tag == atom || prev->tag == list) {
			printf(",");
		}
		else {
			break;
		}
	}
	printf(")");
}

int Depth(GList* head) {
	int depth = 0;
	GList* p = head;
	while (p) {
		if (p->tag == atom) {
			p = p->tail;
		}else if (p->tail == list) {
			if (depth < Depth(p->head)) {
				depth = Depth(p->head);
			}
			p = p->tail;
		}else {
			break;
		}
	}
	return depth += 1;
}

int Length(GList* head) {
	int length = 0;
	GList* p = head;
	while (p) {
		if (p->tag == atom) {
			++length;
			p = p->tail;
		}else if (p->tag == list) {
			length += Length(p->head);
			p = p->tail;
		}else
		{
			break;
		}
	}
	return length;
}

GList* Copy(GList* head) {
	GList* p = head;
	GList* new_head = new(GList);
	GNode* n_p = new_head;
	while (p) {
		if (p->tag == atom) {
			n_p->tag = atom;
			n_p->atom = p->atom;
			p = p->tail;
			n_p->tail = new(GNode);
			n_p = n_p->tail;
		}
		else if (p->tag == list) {
			n_p->tag = list;
			n_p->head = new(GNode);
			n_p->head = Copy(p->head);
			p = p->tail;
			n_p->tail = new(GNode);
			n_p = n_p->tail;
		}
		else if (p == NULL) {
			n_p == NULL;
		}
		else {
			break;
		}
	}
	return head;
}