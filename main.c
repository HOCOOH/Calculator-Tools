#include "Calculator.h"
#include "Functions.h"
#include "Lexer.h"

wordTable words = {{NULL}, 0};

char* peek = NULL;

int main() 
{
    FILE* fp = fopen("../test2.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: Failed to open file\n");
        exit(1);
    }
    char* code = (char*)calloc(CODE_MAX, sizeof(char));
    peek = code;
    char ch = '\0';
    while ((ch = fgetc(fp)) != EOF) {
        *peek++ = ch;
    }
    fclose(fp);

    // 开始分析
    peek = code;
    while (*peek != '\0') {
        Token* tmp = Scan();
        if (tmp->Tag >= 256)
            printf("%3d %d %f %s\n", tmp->Tag, tmp->value, tmp->valueReal, tmp->lexeme);
        else
            printf("%3c %d %f %s\n", tmp->Tag, tmp->value, tmp->valueReal, tmp->lexeme);
    }

    free_s(code);
    return 0;
}

