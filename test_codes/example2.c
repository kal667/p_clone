#include <stdio.h>
#include "pop_direct_branch.c"

void scan_int(int *x)
{
    scanf("%d", x);
    return;
}

int pow2(int x)
{
    return x*x;
}

void foo(int *y)
{
    int p;
    p = pow2(*y);
    *y = p + (*y)*2 + 1;  
}

void print_int(int x)
{
    printf("%d \n", x);
    return;
}

int main()
{
    int a;
    scan_int(&a);
    foo(&a);
    printf("(x+1)^2 = ");
    print_int(a);
    return 0;
}
