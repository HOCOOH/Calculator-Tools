#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int a, b;
} tt;

int main()
{
    tt* t1 = (tt*)malloc(sizeof(tt));
    printf("%p %d %d\n", t1, t1->a, t1->b);

    *t1 = (tt){1, 2};
    printf("%p %d %d\n", t1, t1->a, t1->b);

    
    
    return 0;
}