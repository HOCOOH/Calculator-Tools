#include "Lexer.h"
#include "Parser.h"

#define CODE_MAX 500    // 源代码最大长度

FILE* src = NULL;
FILE* dest = NULL;
char* peek = NULL;
extern Token* look;
extern IdTable ids;

int main(int argc, char* argv[]) {
    /*
    if (argc != 3) {
        printf("Usage: %s inputfile outputfile", argv[0]);
        exit(1);
    }
    if ((src = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "ERROR: Failed to open file \'%s\'\n", argv[1]);
        exit(1);
    }
    if ((dest = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "ERROR: Failed to open file \'%s\'\n", argv[2]);
        exit(1);
    }
    */
    if ((src = fopen("../test/test5.txt", "r")) == NULL) {
        fprintf(stderr, "ERROR: Failed to open file \'%s\'\n", argv[1]);
        exit(1);
    }
    if ((dest = fopen("../test/out5.txt", "w")) == NULL) {
        fprintf(stderr, "ERROR: Failed to open file \'%s\'\n", argv[2]);
        exit(1);
    }
    // 读取源代码存放至code
    char* code = (char*)calloc(CODE_MAX, sizeof(char));
    CheckAllocation(code);
    peek = code;
    char ch = '\0';
    while ((ch = fgetc(src)) != EOF) {
        *peek++ = ch;
    }
    // 开始分析
    peek = code;
    Parser();

    DeleteIdTable();
    free_s(code);
    fclose(src);
    fclose(dest);
    return 0;
}