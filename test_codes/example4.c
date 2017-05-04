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

void pow4(int* x)
{
    int p2;
    p2 = pow2(*x);
    *x = p2*p2;
}

int polynomial(int y)
{
    int p2;
    int p3;
    int p4 = y;
    p2 = pow2(y);
    p3 = pow3(y);
    pow4(&p4);
    return (p4+4*p3+6*p2+4*y+1);  
}

int second_polynomial(int x)
{
    int p;
    int p3;
    p3 = pow3(x);
    p = polynomial(x);
    return (p - 8*p3 - 8*x);
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
    printf("(x+1)^4 = ");
    print_int(p);
    p = second_polynomial(a);
    printf("(x-1)^4 = ");
    print_int(p);
    return 0;
}
