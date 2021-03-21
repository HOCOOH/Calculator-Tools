#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "functions.h"

// 常量宏定义
#define BUF_SIZE 50 // 词素最大长度
#define ID_MAX 50   // 标识符最大数量

// 标识符宏定义
#define NUM 256
#define REAL 257
#define WRITE 258
#define INT 259
#define FLOAT 260

// Token定义
typedef struct {
    int tag;            // 类型标记
    int value;          // 整型属性值
    double valueReal;   // 浮点型属性值
    char* lexeme;       // 字符串型属性值
    bool isAssigned;    // 表示标识符是否被初始化
    bool isID;          // 表示一个Token是否为标识符
} Token;

// 字符表定义
typedef struct {
    Token* tokens[ID_MAX];
    int size;
} IdTable;

// 读取下一个Token
void Scan();

// 在符号表中寻找一个标识符，若找到返回索引值，否则返回-1
int FindId(char* lex);

// 释放符号表的空间
void DeleteIdTable();

#endif