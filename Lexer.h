#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUF_SIZE 50
#define WORD_MAX 50


// 标识符宏定义
#define ID 256
#define NUM 257
#define REAL 258
#define WRITE 260




typedef struct {
    int Tag;
    int value;  // NUM使用
    double valueReal;  // REAL使用
    char* lexeme;  // ID使用


} Token;

typedef struct {
    Token* tokens[WORD_MAX];
    int size;
} wordTable;

Token* Scan();



#endif