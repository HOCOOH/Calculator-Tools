#include "Lexer.h"

int line = 1;
IdTable ids = {{NULL}, 0};
extern char* peek;
extern Token* look;

void Scan() {
    // 跳过空白符号
    for ( ; ; peek++) {
        if ( *peek == ' ' || *peek == '\t')
            continue;
        else if ( *peek == '\n')
            line++;
        else
            break;
    }
    // 标识符的Token储存在符号表中，重新分配新的空间
    if (look == NULL || look->isID == true) {
        look = (Token*)calloc(1, sizeof(Token));
        CheckAllocation(look);
    }
    *look = (Token){0, 0, 0.0, NULL, false, false};

    // 处理数字
    if (ISDIGIT(*peek)) {
        int val = 0;
        do {
            val  = 10 * val + TOVALUE(*peek);
            peek++;
        } while (ISDIGIT(*peek));
        if (*peek != '.') {
            look->tag = NUM;
            look->value = val;
            return;
        }
        double val_r = val, d = 10;
        while (true) {
            peek++;
            if (!ISDIGIT(*peek))
                break;
            val_r += TOVALUE(*peek) / d;
            d *= 10;
        }
        look->tag = REAL;
        look->valueReal = val_r;
        return;
    }

    // 处理标识符及其他字母字符串
    if (ISLETTER(*peek)) {
        char* buf = (char*)calloc(BUF_SIZE, sizeof(char));
        CheckAllocation(buf);
        char* ptr = buf;
        do {
            *ptr++ = *peek++;
        } while (ISLETTER(*peek));
        if (strcmp(buf, "int") == 0) {
            look->tag = INT;
            free_s(buf);
        }
        else if (strcmp(buf, "float") == 0) {
            look->tag = FLOAT;
            free_s(buf);
        }
        else if (strcmp(buf, "write") == 0) {
            look->tag = WRITE;
            free_s(buf);
        }
        else {  // 标识符
            // 在符号表中查找该标识符
            int index = FindId(buf);
            if (index != -1) {  // 找到了
                look = ids.tokens[index];
            }
            else {
                look->isID = true;
                look->lexeme = buf;
                ids.tokens[ids.size++] = look;
            }
        }
        return;
    }

    // 任意单个字符
    look->tag = *peek;
    peek++;
    return;
}

// 在符号表中寻找一个标识符，若找到返回索引值，否则返回-1
int FindId(char* lex) {
    int i = 0;
    for ( ; i < ids.size && strcmp(lex, ids.tokens[i]->lexeme); i++);
    if (i < ids.size)  // 符号表中已存在该标识符
        return i;
    return -1;
}

// 释放符号表的空间
void DeleteIdTable() {
    for (int i = 0; i < ids.size; i++) {
        if (ids.tokens[i]->lexeme != NULL)
            free_s(ids.tokens[i]->lexeme);
        free_s(ids.tokens[i]);
    }
}