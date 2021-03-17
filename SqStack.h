#ifndef SQSTACK_H
#define SQSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100

/*栈定义*/
typedef double ElemType_Sq;
typedef struct {
	ElemType_Sq data[MAXSIZE];  //顺序栈的元素
	int top;  //栈顶指针
} SqStack;

/*函数列表*/
//创建一个空栈
void InitStack(SqStack** ptr_s);

//销毁栈s
void DestroyStack(SqStack** ptr_s);

//判断栈s是否为空
bool IsEmpty(SqStack* s);

//判断栈s是否为满
bool IsFull(SqStack* s);

//进栈
bool Push(SqStack* s, ElemType_Sq e);

//出栈
bool Pop(SqStack* s, ElemType_Sq* ptr_e);

//取栈顶元素
bool GetTop(SqStack* s, ElemType_Sq* ptr_e);

#endif