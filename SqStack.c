#include "SqStack.h"

void InitStack(SqStack** ptr_s) {
	*ptr_s = (SqStack*)malloc(sizeof(SqStack));
	// s = new SqStack;
	(*ptr_s)->top = -1;  //表示栈为空
}

void DestroyStack(SqStack** ptr_s) {
	free(*ptr_s);
	// delete s;
}

bool IsEmpty(SqStack* s) {
	return (s->top == -1);
}

bool IsFull(SqStack* s) {
	return (s->top == MAXSIZE - 1);
}
bool Push(SqStack* s, ElemType_Sq e) {
	if (s->top == MAXSIZE - 1)
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

bool Pop(SqStack* s, ElemType_Sq* ptr_e) {
	if (s->top == -1)
		return false;
	*ptr_e = s->data[s->top];
	s->top--;
	return true;
}

bool GetTop(SqStack* s, ElemType_Sq* ptr_e) {
	if (s->top == -1)
		return false;
	*ptr_e = s->data[s->top];
	return true;
}
