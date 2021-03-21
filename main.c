#include "Lexer.h"
#include "Parser.h"

#define CODE_MAX 500    // 源代码最大长度

char* peek = NULL;
extern Token* look;
extern IdTable ids;

int main() {
    FILE* fp = fopen("../test1.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: Failed to open file\n");
        exit(1);
    }
    // 读取源代码存放至code
    char* code = (char*)calloc(CODE_MAX, sizeof(char));
    CheckAllocation(code);
    peek = code;
    char ch = '\0';
    while ((ch = fgetc(fp)) != EOF) {
        *peek++ = ch;
    }
    fclose(fp);
    // 开始分析
    peek = code;
    Parser();

    DeleteIdTable();
    free_s(code);
    return 0;
}