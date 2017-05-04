#include <stdio.h>
#include "pop_direct_branch.c"

int g = 0;

void scan_int(int *x)
{
    scanf("%d", x);
    return;
}

int pow2(int x)
{
  return x*x;
}

void print_int(int x)
{
    printf("%d, \n", x);
    return;
}

int pow2_clone(int x)
{
    g = x*x;
    pop_direct_branch();
    return x*x;
}

void print_int_clone(int x)
{
    printf("%d, \n", x);
    return;
}

int main ()
{
  int a;
  scan_int(&a);
  int p;
  p = pow2_clone(a);
  p = g;
  printf("pow2 of A = ");
  print_int_clone(p);
  return 0;
}
