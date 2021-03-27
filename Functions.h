#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

// 字符操作
#define IsLetter(x) (IsLower(x) || IsUpper(x))
#define IsDigit(x) (x >= '0' && x <= '9')
#define IsLower(x) (x >= 'a' && x <= 'z')
#define IsUpper(x) (x >= 'A' && x <= 'Z')
#define ToUpper(x) (x = IsLower(x) ? x + 'A' - 'a' : x)
#define ToLower(x) (x = IsUpper(x) ? x + 'a' - 'A' : x)
#define ToValue(x) (x - '0')

// 释放空间并将指针设为NULL
#define free_s(x) {\
    free(x);\
    x = NULL;\
}

// 检查空间分配是否成功
#define CheckAllocation(p) \
    if (p == NULL) {\
        fprintf(stderr, "ERROR: Failed to allocate memory.\n");\
        exit(1);\
    }

#endif