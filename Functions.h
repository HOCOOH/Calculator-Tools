#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#define ISLETTER(x) (ISLOWER(x) || ISUPPER(x))
#define ISDIGIT(x) (x >= '0' && x <= '9')
#define ISLOWER(x) (x >= 'a' && x <= 'z')
#define ISUPPER(x) (x >= 'A' && x <= 'Z')
#define TOUPPER(x) (x = ISLOWER(x)?x + 'A' - 'a':x)
#define TOLOWER(x) (x = ISUPPER(x)?x + 'a' - 'A':x)
#define TOVALUE(x) (x - '0')

// 释放空间并将指针设为NULL
#define free_s(x)\
    {free(x);\
    x = NULL;}

// 检查空间分配是否成功
#define CheckAllocation(p) \
    if (p == NULL) {\
        fprintf(stderr, "ERROR: Failed to allocate memory\n");\
        exit(1);\
    }

#endif