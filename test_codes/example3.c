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

int pow3(int x)
{
    return x*x*x;
}

int polynomial(int y)
{
    int p2;
    int p3;
    p2 = pow2(y);
    p3 = pow3(y);
    return p3+3*p2+3*y+1;  
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
    int p;
    p = polynomial(a);
    printf("(x+1)^3 = ");
    print_int(p);
    return 0;
}
