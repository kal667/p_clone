#include <stdio.h>
#include "pop_direct_branch.c"

void scan_int(int *x)
{
   scanf("%d", x);
   return;
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
    printf("The entered value is: ");
    print_int(a);
    return 0;
}
