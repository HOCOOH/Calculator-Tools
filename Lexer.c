#include "lexer.h"
#include "Functions.h"

int line = 0;

extern wordTable words;
extern char* peek;

Token* Scan() {
    // 跳过空白符号
    for ( ; ; peek++) {
        if ( *peek == ' ' || *peek == '\t')
            continue;
        else if ( *peek == '\n')
            line++;
        else
            break;
    }

    // 处理数字
    if (ISDIGIT(*peek)) {
        int val = 0;
        do {
            val  = 10 * val + *peek - '0';
            peek++;
        } while (ISDIGIT(*peek));
        if (*peek != '.') {
            Token* tmp = (Token*)calloc(1, sizeof(Token));
            CheckAllocation(tmp);
            *tmp = (Token){NUM, val, 0.0, NULL};
            return tmp;
        }
        double val_r = val, d = 10;
        while (true) {
            peek++;
            if (!ISDIGIT(*peek))
                break;
            val_r += TOVALUE(*peek) / d;
            d *= 10;
        }
        Token* tmp = (Token*)calloc(1, sizeof(Token));
        CheckAllocation(tmp);
        *tmp = (Token){REAL, 0, val_r, NULL};
        return tmp;
    }

    // 处理标识符
    if (ISLETTER(*peek)) {
        char* buf = (char*)calloc(BUF_SIZE, sizeof(char));
        CheckAllocation(buf);
        char* ptr = buf;
        do {
            *ptr++ = *peek++;
        } while (ISLETTER(*peek));
        // 在符号表中查找该标识符
        int i = 0;
        for (; i < words.size && strcmp(buf, words.tokens[i]->lexeme); i++);
        if (i < words.size) {  // 符号表中已存在该标识符
            return words.tokens[i];
        }
        else {
            Token* tmp = (Token*)calloc(1, sizeof(Token));
            CheckAllocation(tmp);
            *tmp = (Token){ID, 0, 0.0, buf};
            words.tokens[words.size++] = tmp;
            return tmp;
        }
    }

    // 任意单个字符
    Token* tmp = (Token*)calloc(1, sizeof(Token));
    CheckAllocation(tmp);
    *tmp = (Token){*peek, 0, 0.0, NULL};
    peek++;
    return tmp;
}
